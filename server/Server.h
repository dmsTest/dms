#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "LogThread.h"
#include "ServerSocket.h"

class Server
{
    public:
        Server(LogDao &dao, short port, const std::string ip);
        void dataMine();
        virtual ~Server();
    private:
        StoreThread m_store;
        ServerSocket m_socket;
};

#endif // SERVER_H
