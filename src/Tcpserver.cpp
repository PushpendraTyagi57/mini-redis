#include "Tcpserver.h"
#include "Respparser.h"
#include "Respserializer.h"

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

constexpr int MAX_EVENTS = 64;

TcpServer::TcpServer() : serverSocket(-1), epollFd(-1), dispatcher(store) {}

TcpServer::~TcpServer()
{
    if (serverSocket != -1) close(serverSocket);
    if (epollFd != -1) close(epollFd);
}

bool TcpServer::createSocket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1)
    {
        std::cerr << "Failed to create socket.\n";
        return false;
    }

    return true;
}

bool TcpServer::enableReuseAddress()
{
    int option = 1;

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1)
    {
        std::cerr << "Failed to enable SO_REUSEADDR.\n";
        return false;
    }

    return true;
}

bool TcpServer::bindSocket()
{
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(6379);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1)
    {
        std::cerr << "Bind failed.\n";
        return false;
    }

    return true;
}

bool TcpServer::startListening()
{
    if (listen(serverSocket, SOMAXCONN) == -1)
    {
        std::cerr << "Listen failed.\n";
        return false;
    }

    return true;
}

bool TcpServer::start()
{
    if (!createSocket() || !enableReuseAddress() || !bindSocket() || !startListening())
        return false;

    setNonBlocking(serverSocket);

    epollFd = epoll_create1(0);
    if (epollFd == -1) 
    { 
        std::cerr << "epoll_create1 failed.\n"; 
        return false; 
    }

    epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.fd = serverSocket;

    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, serverSocket, &ev) == -1)
    {
        std::cerr << "Failed to add socket to epoll\n";
        return false;
    }

    runEventLoop();
    return true;
}

bool TcpServer::setNonBlocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    return flags != -1 && fcntl(fd, F_SETFL, flags | O_NONBLOCK) != -1;
}

void TcpServer::runEventLoop()
{
    epoll_event events[MAX_EVENTS];

    while (true)
    {
        int n = epoll_wait(epollFd, events, MAX_EVENTS, -1);

        for (int i = 0; i < n; ++i)
        {
            int fd = events[i].data.fd;

            if (fd == serverSocket)
                acceptClient();
            else if (events[i].events & (EPOLLHUP | EPOLLERR))
                closeClient(fd);
            else if (events[i].events & EPOLLIN)
                handleClientReadable(fd);
        }
    }
}

void TcpServer::acceptClient()
{
    while (true)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK) break;

            std::cerr << "accept failed\n";
            break;
        }

        setNonBlocking(clientSocket);

        epoll_event ev{};
        ev.events = EPOLLIN;
        ev.data.fd = clientSocket;

        if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientSocket, &ev) == -1)
        {
            std::cerr << "Failed to add socket to epoll\n";
            close(clientSocket);
            continue;
        }

        clients[clientSocket] = ClientConnection{};
        std::cout << "Client connected.\n";
    }
}

void TcpServer::handleClientReadable(int clientSocket)
{
    char buffer[4096];

    while (true)
    {
        ssize_t n = recv(clientSocket, buffer, sizeof(buffer), 0);
        
        if (n > 0)
        { 
            clients[clientSocket].inputBuffer.append(buffer, n); 
            continue; 
        }

        if (n == 0) 
        { 
            closeClient(clientSocket); 
            return; 
        }

        break;
    }

    auto& inbuf = clients[clientSocket].inputBuffer;
    RespParser parser;

    while (true)
    {
        size_t pos = 0;
        try
        {
            auto commands = parser.parse(inbuf, pos);
            std::string response = dispatcher.dispatch(commands);
            send(clientSocket, response.c_str(), response.size(), 0);
            inbuf.erase(0, pos);
        }
        catch (const IncompleteRequest&)
        {
            break;
        }
        catch (const std::exception& e)
        {
            std::string errorResponse = RespSerializer::error(e.what());
            send(clientSocket, errorResponse.c_str(), errorResponse.size(), 0);
            inbuf.clear();
            break;
        }
    }
}

void TcpServer::closeClient(int clientSocket)
{
    epoll_ctl(epollFd, EPOLL_CTL_DEL, clientSocket, nullptr);
    close(clientSocket);
    clients.erase(clientSocket);
    std::cout << "Client disconnected.\n";
}