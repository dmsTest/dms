#ifndef  __WORKER_H_
#define __WORKER_H_

#include "singleton.h"
#include "tcp_server.h"

class TcpServer;

//handle and send msg
class Worker : public Noncopyable
{
public:
	explicit Worker() { };
	~Worker() {};

	void sendMessage(TcpServer *);
	void handleMessage(TcpServer *);
private:

};

#endif