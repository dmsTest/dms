#ifndef  __TCP_SERVER_H_
#define __TCP_SERVER_H_

#include "singleton.h"
#include "tcp_client.h"
#include "mutex.h"
#include "worker.h"
#include "epoller.h"
#include "thread_pool.h"
#include "socket.h"
#include "safe_list.h"
#include "net_base.h"
#include "epoller.h"
#include <utility>
#include <assert.h>
#include <sys/epoll.h>
#include <map>

#define WORKER_NUM 5
#define SAFE_DELETE(ptr) do { if( ptr != NULL ) delete ptr; \
		} while(0)

#define SER_PORT 8888

using namespace std;

class Worker;
class TcpClient;
class Epoller;

class TcpServer : public Noncopyable
{
public:
	//<sockfd,TcpClient>
	typedef std::map<int,TcpClient*> ClientMap;
	explicit TcpServer();
	bool init();
	void loop();
	void update(int operation,int connfd,int events = EPOLLIN);
	void readClientData(int connfd);
	pair<int,message_base * > getRecvFront();
	TcpClient* getTcpClient(int connfd);
	void addMessage(int conn,message_base *msg);
	pair<int,message_base * > getMessage();
	
	~TcpServer();
private:
	int epollfd_;
	Socket listen_sock_;
	ClientMap client_map_;
	Mutex mutex_;
	Condition cond_;

	Epoller *epoller_;
	//Acceptor acceptor_;
	//begin is send,nexts are handle
	Worker *worker_;
	Threadpool thread_pool_;
	bool quit_;

	SafeList<pair<int,message_base*> > recvQueue;
	SafeList<pair<int,message_base*> > sendQueue;
};

#endif