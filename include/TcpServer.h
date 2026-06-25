#pragma once

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();
    bool start();
    bool enableReuseAddress();

private:
    bool createSocket();
    bool bindSocket();
    bool startListening();
    void acceptClients();
    void handleClients(int clientSocket);

private:
    int serverSocket;
};
g