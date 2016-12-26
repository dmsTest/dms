#ifndef  __NET_HANDLE_H_
#define __NET_HANDLE_H_

#include "singleton.h"
#include "net_base.h"
#include "tcp_client.h"
#include <functional>
#include <map>

using namespace std;

/*
#define REGISTER_FUNC(net_struct,_func) register_handle_func(#net_struct,_func)

// # will conver to the const char*,and ignore the spaces
#define UNREGISTER_FUNC(net_struct,_func) ungister_handle_func(#net_struct,_func)
*/

// handle recved msg
class Net_handle :  public Noncopyable
{
public:
	typedef std::function<int (message_base*)> handle_func;
	typedef map<unsigned int, handle_func> handle_map;
public:
	Net_handle(Tcp_client *_tcp_client);
	~Net_handle();
	void register_handle_func(const char *sz_message_name_,handle_func _func);
	void ungister_handle_func(const char *sz_message_name_,handle_func _func);

	void handle_message(message_base *msg);
	// msg handle
	int handle_register(message_base *msg);
	int handle_login(message_base *msg);
private:
	handle_map func_map;
	Tcp_client *tcp_client;
};

#endif