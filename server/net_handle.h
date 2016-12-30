#ifndef  __NET_HANDLE_H_
#define __NET_HANDLE_H_

#include "singleton.h"
#include "log_dao.h"
#include "tcp_server.h"
#include "tcp_client.h"
#include <functional>

class TcpClient;

using namespace std;

class NetHandle : public Noncopyable
{
public:
	typedef std::function<int(message_base*)> handle_func;
	typedef map<unsigned int, handle_func> handle_map;

	NetHandle(TcpClient *tcp_client);
	~NetHandle();

	void register_handle_func(const char *sz_message_name,handle_func _func);
	void ungister_handle_func(const char *sz_message_name);

	void send_message(message_base *msg,int msg_size);
	void handle_message(message_base *msg);
	// msg handle
	int handle_register(message_base *msg);
	int handle_login(message_base *msg);
	int handle_data(message_base *msg);

private:
	handle_map handle_map_;

	TcpClient *tcp_client_;
	MysqlDao *sql_dao_;

};

#endif