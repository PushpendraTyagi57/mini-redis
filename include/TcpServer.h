#pragma once

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();
    bool start();

private:
    bool createSocket();
    bool bindSocket();
    bool startListening();
    void acceptClients();

private:
    int serverSocket;
};