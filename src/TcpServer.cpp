#include "TcpServer.h"

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

TcpServer::TcpServer() : serverSocket(-1)
{
}

TcpServer::~TcpServer()
{
    if (serverSocket != -1)
    {
        close(serverSocket);
    }
}

bool TcpServer::start()
{
    if (!createSocket())
        return false;

    if (!enableReuseAddress())
        return false;

    if (!bindSocket())
        return false;

    if (!startListening())
        return false;

    acceptClients();

    return true;
}

bool TcpServer::createSocket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (serverSocket == -1)
    {
        std::cerr << "Failed to create socket.\n";
        return false;
    }

    std::cout << "Socket created.\n";

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

    std::cout << "SO_REUSEADDR enabled.\n";

    return true;
}

bool TcpServer::bindSocket()
{
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(6379);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //Binding socket to port 6379
    if (bind(serverSocket,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)) == -1)
    {
        std::cerr << "Bind failed.\n";
        return false;
    }
    
    std::cout << "Socket bound to port 6379.\n";

    return true;
}

bool TcpServer::startListening()
{
    //starting to listen for incoming connections...
    if (listen(serverSocket, SOMAXCONN) == -1)
    {
        std::cerr << "Listen failed.\n";
        return false;
    }

    std::cout << "Listening on port 6379..\n";

    return true;
}

void TcpServer::acceptClients()
{
    while (true)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == -1)
        {
            std::cerr << "Accept failed.\n";
            continue;
        }

        std::cout << "Client connected.\n";

        handleClients(clientSocket);

        close(clientSocket);
    }
}

void TcpServer::handleClients(int clientSocket)
{
    char buffer[1024];
    while (true)
    {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesReceived == -1)
        {
            std::cerr << "Falied to receive data.\n";
            return;
        }

        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected.\n";
            return;
        }

        std::string message(buffer, bytesReceived);

        std::cout << "Received: " << message << '\n';

        ssize_t bytesSent = send(clientSocket, message.c_str(), message.size(), 0);

        if (bytesSent == -1)
        {
            std::cerr << "Failed to send data.\n";
            return;
        }

        std::cout << "Sent: " << message << '\n';
    }
}