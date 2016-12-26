#include "net_handle.h"
#include "client_log.h"
#include "singleton.h"
#include <utility>
#include <iostream>
#include <functional>

Net_handle::Net_handle(Tcp_client *_tcp_client)
	: tcp_client(_tcp_client)
{
	register_handle_func("NET_S2C_register",std::bind(&Net_handle::handle_register,this,std::placeholders::_1));
	//register_handle_func("NET_C2S_login",&Net_handle::handle_login);

}

Net_handle::~Net_handle()
{
	//ungister_handle_func("NET_S2C_register",&Net_handle::handle_register);
	//ungister_handle_func("NET_C2S_login",&Net_handle::handle_login);

	func_map.clear();
}

void Net_handle::register_handle_func(const char *sz_message_name,handle_func _func)
{
	unsigned int crc_id = message_id_crc(sz_message_name);
	func_map.insert(make_pair(crc_id,_func));
}

void Net_handle::ungister_handle_func(const char *sz_message_name,handle_func _func)
{
	unsigned int crc_id = message_id_crc(sz_message_name);
	func_map.erase(crc_id);
}

void Net_handle::handle_message(message_base *msg)
{
	handle_func func;
	map<unsigned int,handle_func>::iterator it_find = func_map.find(msg->msg_id);
	if( it_find == func_map.end() )
	{
		Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"can't find the msg_id: %d\n",msg->msg_id);
		return;
	}
	func = it_find->second;
	int error = func(msg);
	if( error != 0 )
	{
		Singleton<Log>::getInstance()->write_log(E_LOG_ERROR,"handle the msg_id: %d error num: %d\n",msg->msg_id,error);		
	}
}

int Net_handle::handle_register(message_base *msg)
{
	NET_S2C_register *p_msg = static_cast<NET_S2C_register*>(msg);
	if( !p_msg )
	{
		return -1;
	}
	if( p_msg->err_code == E_RS_SUCCESS )
	{
		// register success,then login also success
		Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","register success");
		//cout << "register success" << endl;
		tcp_client->set_register(true);
		tcp_client->set_login(true);
	}
	else
	{
		// register fail
		Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","register fail");
		cout << "register fail" << endl;
	}
	return 0;
}

int Net_handle::handle_login(message_base *msg)
{
	NET_S2C_login *p_msg = static_cast<NET_S2C_login*>(msg);
	if( !p_msg )
	{
		return -1;
	}
	if( p_msg->err_code == E_LS_SUCCESS )
	{
		// login success
		Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","login success");
		//cout << "login success" << endl;
		tcp_client->set_login(true);
	}
	else
	{
		// login fail
		Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","login fail");
		cout << "login fail" << endl;
	}
	return 0;
}