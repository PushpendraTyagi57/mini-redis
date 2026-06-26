#pragma once

#include "Store.h"

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
    void acceptClients();
    void handleClients(int clientSocket);

private:
    int serverSocket;
    Store store;
};