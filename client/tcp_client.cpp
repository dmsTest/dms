#include "tcp_client.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include "data.h"
#include "client_log.h"
#include "log_reader.h"
#include "net_handle.h"

Tcp_client::Tcp_client(string _ip,short _port) :
	m_ip(_ip),
	m_port(_port),
	m_state(E_TS_NOT_CONNECT),
	m_register(false),
	m_login(false)
{

}

Tcp_client::~Tcp_client()
{
	if( m_state == E_TS_CONNECT )
	{
		shutdown_socket();
	}
}

int Tcp_client::connect_server(int nsec)
{
	m_sockfd = socket(AF_INET,SOCK_STREAM,0);
	int opt = 1;
	setsockopt(m_sockfd,IPPROTO_TCP,TCP_NODELAY,&opt,sizeof(opt));
	struct sockaddr_in sa_in;
	bzero(&sa_in,sizeof(sa_in));
	sa_in.sin_family = AF_INET;
	sa_in.sin_port = htons(m_port);
	if( inet_pton(AF_INET,m_ip.c_str(),&sa_in.sin_addr) < 0 )
		oops("inet_pton error",1);

	socklen_t sa_len = sizeof(sa_in);
	int flags,n,error;
	socklen_t len;
	fd_set rset,wset;
	struct timeval tval;
	
	flags = fcntl(m_sockfd,F_GETFL,0);
	fcntl(m_sockfd,F_SETFL,flags | O_NONBLOCK);
	
	error = 0;
	if( (n = connect(m_sockfd,(struct sockaddr*)&sa_in,sa_len)) < 0 )
	{
		if( errno != EINPROGRESS )
			return -1;
	} 
	if( n == 0 )
		goto done;		// 成功连接则直接跳到done
	FD_ZERO(&rset);
	FD_SET(m_sockfd,&rset);

	wset = rset;
	tval.tv_sec = nsec;
	tval.tv_usec = 0;
	if( (n = select(m_sockfd + 1,&rset,&wset,NULL,nsec?&tval:NULL)) == 0 )
	{
		close(m_sockfd);
		errno = ETIMEDOUT;
		return -1;
	}
	if( FD_ISSET(m_sockfd,&rset) || FD_ISSET(m_sockfd,&wset) )
	{
		len = sizeof(error);
		if( getsockopt(m_sockfd,SOL_SOCKET,SO_ERROR,&error,&len) < 0 )
			return -1;
	}
	else
	{
		oops("select error",1);
	}
done:
	fcntl(m_sockfd,F_SETFL,flags);
	if( error )
	{
		close(m_sockfd);
		errno = error;
		return -1;
	}
	m_state = E_TS_CONNECT;
	pthread_create(&m_send_tid,NULL,send_thread_func,this);
	pthread_create(&m_recv_tid,NULL,recv_thread_func,this);
	return 0;
}

void Tcp_client::shutdown_socket(int nsec)
{
	// wait send the message
	sleep(nsec);
	m_state = E_TS_SHUTDOWN;
	pthread_join(m_send_tid,NULL);
	pthread_join(m_recv_tid,NULL);
	pthread_join(m_work_tid,NULL);
	message_base *p_item;
	while( !m_send_queue.empty() )
	{
		p_item = m_send_queue.pop_front();
		delete p_item;
		p_item = NULL;
	}
	while( !m_recv_queue.empty() )
	{
		p_item = m_recv_queue.pop_front();
		delete p_item;
		p_item = NULL;
	}
	shutdown(m_sockfd,SHUT_RD);
}

void Tcp_client::send_message(message_base *msg,int message_size)
{
	char *msg_copy = new char[message_size];
	memmove(msg_copy,msg,message_size);
	message_base *p_item = reinterpret_cast<message_base*>(msg_copy);
	if( p_item == nullptr)
	{
		delete[] msg_copy;
	}
	m_send_queue.push_back(p_item);
}

void* Tcp_client::send_thread_func(void *arg)
{
	message_base *p_item = NULL;
	Tcp_client *p_tcp_client = static_cast<Tcp_client*>(arg);
	if( !p_tcp_client )
	{
		Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","arg convert to tcp_client error");
		return NULL;
	}
	int server_fd = p_tcp_client->m_sockfd;
	while( p_tcp_client->m_state != E_TS_SHUTDOWN )
	{
		// there will block 2 sec,wait for message send to server
		p_item = p_tcp_client->m_send_queue.pop_front();
		if( !p_item )
			continue;
		// send to server,the msg size
		int msg_size = p_item->msg_size;
		// encrypt
		encrypt_msg((char*)&msg_size,sizeof(int));
		write(server_fd,(char*)&msg_size,sizeof(int));
		// encrypt
		encrypt_msg((char*)p_item,p_item->msg_size);
		// send to server the msg
		writen(server_fd,(char*)p_item,p_item->msg_size);

		delete p_item;
	}
	return NULL;
}

void* Tcp_client::recv_thread_func(void *arg)
{
	Tcp_client *p_tcp_client = static_cast<Tcp_client*>(arg);
	if( !p_tcp_client )
	{
		Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","arg convert to tcp_client error");
		return NULL;
	}
	E_READ_STATE read_state = E_RS_SIZE;
	int server_fd = p_tcp_client->m_sockfd;
	int msg_size = 0;
	int read_n;
	fd_set read_set;
	FD_ZERO(&read_set);
	FD_SET(server_fd,&read_set);
	int max_fd = server_fd;
	struct timeval tv;
	tv.tv_sec = WAIT_READ_SEC;
	tv.tv_usec = 0;
	while( p_tcp_client->m_state != E_TS_SHUTDOWN )
	{
		// select server_fd
		int ready = select(max_fd + 1,&read_set,NULL,NULL,&tv);
		if( ready < 0)
		{
			Singleton<Log>::getInstance()->write_log(E_LOG_ERROR,"%s\n","select ready error");	
			break;
		}
		else if( ready == 0 )
		{
			FD_SET(server_fd,&read_set);
			continue;
		}
		else
		{
			if( read_state == E_RS_SIZE)
			{
				read_n = read(server_fd,&msg_size,sizeof(int));
				if( read_n != sizeof(int) )
				{
					Singleton<Log>::getInstance()->write_log(E_LOG_ERROR,"read server socket size error,size: %d/n",read_n);
					break;
				}
				if( msg_size == 0 )
				{
					Singleton<Log>::getInstance()->write_log(E_LOG_ERROR,"%s\n","read size = 0,shutdown the socket");
					break;
				}
				// decrypt
				decrypt_msg((char*)&msg_size,sizeof(int));
				read_state = E_RS_DATA;
			}
			else
			{
				char *buf_data = new char[msg_size];
				memset(buf_data,'\0',msg_size);
				readn(server_fd,buf_data,msg_size);
				// decrypt
				decrypt_msg(buf_data,msg_size);
				message_base *p_item = reinterpret_cast<message_base*>(buf_data);
				p_tcp_client->m_recv_queue.push_back(p_item);
				read_state = E_RS_SIZE;
			}
		}
	}
	return NULL;
}

void* Tcp_client::work_thread_func(void *arg)
{
	Tcp_client *p_tcp_client = static_cast<Tcp_client*>(arg);
	if( !p_tcp_client )
	{
		Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","arg convert to tcp_client error");
		return NULL;
	}
	message_base *p_item;
	Net_handle handle_item(p_tcp_client);
	while( p_tcp_client->m_state != E_TS_SHUTDOWN )
	{
		// would block this thread
		p_item = p_tcp_client->m_recv_queue.pop_front();
		if( !p_item )
			continue;
		// handle the msg:p_item
		handle_item.handle_message(p_item);
		// delete p_item
		delete p_item;
		p_item = NULL;
	}
	return NULL;
}
