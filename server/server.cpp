#include "Server.h"

Server::Server(LogDao &dao, short port, const std::string ip) : m_store(dao),m_socket(port,ip)
{

}

void Server::dataMine()
{
    m_store.start();
    std::cout << "--------start accept client--------" << std::endl;
    m_socket.acceptClient();
}

Server::~Server()
{
    //dtor
}