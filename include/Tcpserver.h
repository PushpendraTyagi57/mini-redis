#pragma once

#include "Store.h"
#include "CommandDispatcher.h"
#include <string>
#include <unordered_map>

struct ClientConnection
{
    std::string inputBuffer;
};

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();
    bool start();

private:
    bool enableReuseAddress();
    bool createSocket();
    bool bindSocket();
    bool startListening();
    bool setNonBlocking(int fd);
    void runEventLoop();
    void acceptClient();
    void handleClientReadable(int clientSocket);
    void closeClient(int clientSocket);

private:
    int serverSocket;
    int epollFd;
    Store store;
    CommandDispatcher dispatcher;
    std::unordered_map<int, ClientConnection> clients;
};