#ifndef  __EPOLLER_H_
#define __EPOLLER_H_

#include "singleton.h"
#include "tcp_server.h"
#include <vector>
#include <sys/epoll.h>

class Epoller : public Noncopyable
{
public:
	typedef std::vector<struct epoll_event> EventList;

	static const int kInitEventListSize = 16; 
	
	Epoller() {}
	
	Epoller(int epollfd) : epollfd_(epollfd),events_(kInitEventListSize){ }

	void run(TcpServer *);
	
	~Epoller();
private:
	int epollfd_;
  	EventList events_;

};

#endif