#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <string>
#include "ServerException.h"
#include "LogThread.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class ServerSocket
{
    public:
        ServerSocket(short port, const std::string ip);
        void acceptClient() throw(SocketException);
        virtual ~ServerSocket();
    private:
        int m_sockfd;
};

#endif // SERVERSOCKET_H
