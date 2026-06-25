#include <iostream>
#include "TcpServer.h"

int main()
{
    TcpServer server;
    if (!server.start())
    {
        std::cerr << "Failed to start TCP Server.\n";
        return 1;
    }
    return 0;
}