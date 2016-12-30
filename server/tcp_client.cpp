#include "tcp_client.h"

TcpClient::TcpClient(Socket &_sock,TcpServer *tcp_server) : sock_(_sock),tcp_server_(tcp_server),read_state_(ReadSize)
	,read_size_(0)
{
	net_handle_ = new NetHandle(this);
}

TcpClient::~TcpClient()
{
	if( net_handle_ != NULL)
		delete net_handle_;
}

size_t TcpClient::readSize()
{
	size_t readn = 0;
	readn = sock_.read(&read_size_,sizeof(read_size_));

	read_state_ = ReadData;
	return readn;
}

size_t TcpClient::readData(char *buf_data,size_t count)
{
	size_t readn = 0;
	readn = sock_.readn(buf_data,count);
	
	read_state_ = ReadSize;
	return readn;
}

void TcpClient::sendMessage(message_base *msg,int msg_size)
{
	char *msg_copy = new char[msg_size];
	memmove(msg_copy,msg,msg_size);
	message_base *p_item = reinterpret_cast<message_base*>(msg_copy);
	if( p_item == nullptr)
	{
		delete[] msg_copy;
		return;
	}
	tcp_server_->addMessage(sock_.sockfd(),p_item);
}