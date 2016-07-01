#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <string>

class ServerSocket
{
    public:
        ServerSocket(short port, const std::string ip);
        void acceptClient();
        virtual ~ServerSocket();
    private:
        int m_sockfd;
};

#endif // SERVERSOCKET_H
