#include "tcp_server.h"
#include <functional>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>


TcpServer::TcpServer() : epollfd_(epoll_create1(EPOLL_CLOEXEC)) ,mutex_(),
	cond_(mutex_),quit_(false)
{
	epoller_ = new Epoller(epollfd_);
}

TcpServer::~TcpServer()
{
	thread_pool_.stop();
	close(epollfd_);
	TcpClient *tcp_client = NULL;
	for(ClientMap::iterator it = client_map_.begin(); it != client_map_.end(); ++it)
	{
		tcp_client = it->second;
		delete tcp_client;
		tcp_client = NULL;
	}
	client_map_.clear();
	SAFE_DELETE(worker_);
}

bool TcpServer::init()
{
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	if( listenfd < 0 )
		return false;
	listen_sock_.setSockfd(listenfd);
	listen_sock_.setReuseAddr(1);
	listen_sock_.setKeepAlive(1);
	listen_sock_.setTcpNoDelay(1);
	struct sockaddr_in sa_in;
	bzero(&sa_in,sizeof(sa_in));
	sa_in.sin_family = AF_INET;
	sa_in.sin_port = htons(SER_PORT);
	sa_in.sin_addr.s_addr = htonl(INADDR_ANY);
	listen_sock_.bind((struct sockaddr*)&sa_in);

	worker_ = new Worker[WORKER_NUM];
	if( worker_ == NULL)
		return false;
	//thread_pool_.add_task(std::bind(&Acceptor::run,&acceptor_,this));
	thread_pool_.add_task(std::bind(&Epoller::run,epoller_,this));
	thread_pool_.add_task(std::bind(&Worker::sendMessage,&worker_[0],this));
	for(int i = 1; i < WORKER_NUM; ++i)
	{
		thread_pool_.add_task(std::bind(&Worker::handleMessage,&worker_[i],this));
	}
	return true;
}

// accept the client,add to server
void TcpServer::loop()
{
	quit_ = false;
	while( !quit_ )
	{
		int connfd = listen_sock_.accept();
		if( connfd < 0 )
			continue;
		Socket connsock(connfd);
		connsock.setKeepAlive(1);
		connsock.setTcpNoDelay(1);
		TcpClient *new_tcp_client = new TcpClient(connsock,this);
		mutex_.lock();
		client_map_.insert(make_pair(connfd,new_tcp_client));
		update(connfd,EPOLL_CTL_ADD);
		mutex_.unlock();
	}
}

void TcpServer::update(int operation,int connfd,int events)
{
	struct epoll_event event;
  	bzero(&event, sizeof event);
  	event.events = events;
  	epoll_ctl(epollfd_, operation, connfd, &event);
}

void TcpServer::readClientData(int connfd)
{
	mutex_.lock();
	ClientMap::iterator it_find = client_map_.find(connfd);
	if( it_find == client_map_.end() )
	{
		mutex_.unlock();
		return;
	}
	TcpClient *tcp_client = it_find->second;
	size_t readn = 0;
	int read_size = 0;
	if( tcp_client->read_state() == ReadSize )
	{
		readn = tcp_client->readSize();
	}
	else
	{
		read_size = tcp_client->read_size();
		assert(read_size >0 && read_size < MAX_LINE);
		char buf[read_size];
		readn = tcp_client->readData(buf,read_size);
		message_base *p_item = reinterpret_cast<message_base*>(buf);
		if( p_item != NULL)
		{
			recvQueue.push_back(make_pair(connfd,p_item));
		}
	}
	
	if( read_size == 0 )
	{
		delete tcp_client;
		client_map_.erase(it_find);
	}
	mutex_.unlock();
}

pair<int,message_base * > TcpServer::getRecvFront()
{
	// would block
	return recvQueue.pop_front();
}

TcpClient* TcpServer::getTcpClient(int connfd)
{
	mutex_.lock();
	ClientMap::iterator it_find = client_map_.find(connfd);
	if( it_find != client_map_.end() )
	{
		mutex_.unlock();
		return it_find->second;
	}
	mutex_.unlock();
	return NULL;
}

void TcpServer::addMessage(int connfd,message_base *msg)
{
	sendQueue.push_back(make_pair(connfd,msg));
}

pair<int,message_base * > TcpServer::getMessage()
{
	return sendQueue.pop_front();
}