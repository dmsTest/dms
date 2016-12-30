#include "net_handle.h"
#include "net_base.h"
#include <functional>

NetHandle::NetHandle(TcpClient *tcp_client) : tcp_client_(tcp_client)
{
	sql_dao_ = new MysqlDao("root","123456");
	register_handle_func("NET_C2S_register",std::bind(&NetHandle::handle_register,this,std::placeholders::_1));
	register_handle_func("NET_C2S_login",std::bind(&NetHandle::handle_login,this,std::placeholders::_1));
	register_handle_func("NET_C2S_match_data",std::bind(&NetHandle::handle_data,this,std::placeholders::_1));
}

NetHandle::~NetHandle()
{
	ungister_handle_func("NET_C2S_register");
	ungister_handle_func("NET_C2S_login");
	ungister_handle_func("NET_C2S_match_data");

	handle_map_.clear();
}

void NetHandle::register_handle_func(const char *sz_message_name,handle_func _func)
{
	unsigned int msg_id = message_id_crc(sz_message_name);

	handle_map_.insert(make_pair(msg_id,_func));
}

void NetHandle::ungister_handle_func(const char *sz_message_name)
{
	unsigned int msg_id = message_id_crc(sz_message_name);

	handle_map_.erase(msg_id);
}

void NetHandle::send_message(message_base *msg,int msg_size)
{
	//add to send queue
	tcp_client_->sendMessage(msg,msg_size);
}

void NetHandle::handle_message(message_base *msg)
{
	handle_map::iterator it_find = handle_map_.find(msg->msg_id);
	if( it_find == handle_map_.end() )
		return;

	handle_func handle_func_find = it_find->second;
	handle_func_find(msg);
}

int NetHandle::handle_register(message_base *msg)
{
	NET_C2S_register *msg_net = static_cast<NET_C2S_register*>(msg);
	if( msg_net == NULL )
		return -1;
	NET_S2C_register send;
	bool is_insert = sql_dao_->insertUser(msg_net->user_name,msg_net->user_password,msg_net->gender,msg_net->phone);
	if( is_insert )
	{
		send.err_code = E_RS_SUCCESS;
	}
	else
	{
		send.err_code = E_RS_FAILURE;
	}
	send_message(&send,send.msg_size);
	return 0;
}

int NetHandle::handle_login(message_base *msg)
{
	NET_C2S_login *msg_net = static_cast<NET_C2S_login*>(msg);
	if( msg_net == NULL )
		return -1;
	NET_S2C_login send;
	bool is_exit = sql_dao_->queryUser(msg_net->user_name,msg_net->user_password);
	if( is_exit )
	{
		send.err_code = E_LS_SUCCESS;
	}
	else
	{
		send.err_code = E_LS_FAILURE;
	}
	send_message(&send,send.msg_size);
	return 0;
}

int NetHandle::handle_data(message_base *msg)
{
	NET_C2S_match_data *msg_net = static_cast<NET_C2S_match_data*>(msg);
	if( msg_net == NULL )
		return -1;
	sql_dao_->insert(msg_net->log_data);
	return 0;
}