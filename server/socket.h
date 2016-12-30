#ifndef  __SOCKET_H_
#define __SOCKET_H_

#include <netinet/in.h>

class Socket
{
public:
	explicit Socket(int sockfd = 0) : sockfd_(sockfd) { }
	~Socket();

	int sockfd() const { return sockfd_; }
	void setSockfd(int &sockfd) { sockfd_ = sockfd; }
	int accept();
	void listen(int listen_num = 1024);
	void bind(struct sockaddr *addr);
	bool getsockaddr(struct sockaddr &);

	void shutdownWrite();

	void setReusePort(bool on);
	void setTcpNoDelay(bool on);

	void setReuseAddr(bool on);
	void setKeepAlive(bool on);

	ssize_t write(void *buf, size_t count);
	ssize_t writen(void *vptr,size_t n);
	ssize_t read(void *buf, size_t count);
	ssize_t readn(void *buf,size_t n);

private:
	int sockfd_;
};

#endif