#include "epoller.h"
#include <sys/epoll.h>

Epoller::~Epoller()
{
	
}

//add msg to blockqueue,read all client
void Epoller::run(TcpServer *tcp_server)
{
	int nready;

	for( ; ; )
	{
		nready = epoll_wait(epollfd_,&*events_.begin(),static_cast<int>(events_.size()), -1);
		for( int i = 0; i < nready; ++i )
		{
			int connfd = events_[i].data.fd;
			tcp_server->readClientData(connfd);
		}
	}
}