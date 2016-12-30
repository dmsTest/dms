#include "worker.h"

//send all msg
void Worker::sendMessage(TcpServer *tcp_server)
{
	// send all message
	for( ; ; )
	{
		// would block
		pair<int,message_base*> msg = tcp_server->getMessage();
		Socket sock_tmp(msg.first);
		sock_tmp.write(&(msg.second->msg_size),sizeof(int));
		sock_tmp.writen(msg.second,msg.second->msg_size);
		delete msg.second;
	}
}

//handle all msg
void Worker::handleMessage(TcpServer *tcp_server)
{
	for( ; ; )
	{
		pair<int,message_base*> msg = tcp_server->getRecvFront();
		TcpClient *tcp_client = tcp_server->getTcpClient(msg.first);
		NetHandle *msg_handle = tcp_client->net_handle();
		msg_handle->handle_message(msg.second);
		delete msg.second;
	}
}