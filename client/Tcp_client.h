#ifndef  __TCP_CLIENT_H_
#define __TCP_CLIENT_H_

#include <string>
#include <pthread.h>
#include "Singleton.h"
#include "Net_base.h"
#include "SafeList.h"

using namespace std;

#define SERVER_IP       "127.0.0.1"
#define SERVER_PORT  8888
#define WAIT_READ_SEC 2

#define TCP_CLIENT_SEND(msg,msg_size)  do {  \
		Singleton<Tcp_client>::getInstance()->send_message(msg,msg_size);  \
	} while(0)

enum E_TCP_STATE
{
	E_TS_NOT_CONNECT = -1,
	E_TS_CONNECT,
	E_TS_SHUTDOWN,
	E_TS_CLOSE
};

enum E_READ_STATE
{
	E_RS_SIZE = 0,
	E_RS_DATA
};

class Tcp_client : public Noncopyable
{
public:
	Tcp_client(string _ip = SERVER_IP,short _port = SERVER_PORT);
	~Tcp_client();
	int connect_server(int nsec = 3);
	void shutdown_socket(int nsec = 3);

	void send_message(message_base *msg, int message_size);
	inline bool is_register() { return m_register; }
	inline void set_register(bool _register) { m_register = _register;}
	inline bool is_login() { return m_login;}
	inline void set_login(bool _login) { m_login = _login; }
private:
	static void* send_thread_func(void *arg);
	static void* recv_thread_func(void *arg);
	static void* work_thread_func(void *arg);
	string m_ip;
	short m_port;
	int m_sockfd;
	E_TCP_STATE m_state;
	volatile bool m_register;
	volatile bool m_login;
	SafeList<message_base*> m_send_queue;
	SafeList<message_base*> m_recv_queue;
	pthread_t m_send_tid;
	pthread_t m_recv_tid;
	pthread_t m_work_tid;
};

#endif