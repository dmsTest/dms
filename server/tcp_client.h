#ifndef  __TCP_CLIENT_H_
#define __TCP_CLIENT_H_

#include "singleton.h"
#include "socket.h"
#include "net_handle.h"
#include "log_dao.h"
#include "tcp_server.h"
#include <string>
#include <sys/epoll.h>

#define MAX_LINE 4096

enum ReadState
{
	ReadSize = 0,
	ReadData
};

class TcpServer;
class NetHandle;

class TcpClient : public Noncopyable
{
public:
	TcpClient(Socket &_sock,TcpServer *tcp_server);
	~TcpClient();

	Socket socket() const { return sock_; }
	int sockfd() const { return sock_.sockfd(); }
	std::string user_name() const { return user_name_; }

	ReadState read_state() { return read_state_; }
	void set_read_state(ReadState rs) { read_state_ = rs; }

	int read_size() { return read_size_; }
	void set_read_size(int read_size) { read_size_ = read_size; }
	void setuser_name(std::string &_user_name) { user_name_ = _user_name; }
	NetHandle* net_handle() { return net_handle_; }
	void sendMessage(message_base *msg,int msg_size);
	
	size_t readSize();
	size_t readData(char *buf_data,size_t count);
private:
	Socket sock_;
	TcpServer *tcp_server_;
	NetHandle *net_handle_;
	
	std::string user_name_;
	ReadState read_state_;
	int read_size_;
};

#endif