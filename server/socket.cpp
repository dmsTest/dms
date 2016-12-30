#include "socket.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include  <netinet/in.h>
#include <netinet/tcp.h>
#include "net_base.h"

Socket::~Socket()
{
	close(sockfd_);
}

bool Socket::getsockaddr(struct sockaddr &sock_addr)
{
	memset(&sock_addr,0,sizeof(sock_addr));
	socklen_t addr_len = sizeof(sock_addr);

	if( getpeername(sockfd_,&sock_addr,&addr_len) < 0)
	{
		return false;
	}

	return true;
}

int Socket::accept()
{
	int connfd = ::accept(sockfd_,(struct sockaddr*)NULL,NULL);
	return connfd;
}

void Socket::listen(int listen_num)
{
	::listen(sockfd_,listen_num);
}

void Socket::bind(struct sockaddr *addr)
{
	::bind(sockfd_,addr,sizeof(*addr));
}

void Socket::shutdownWrite()
{
	::shutdown(sockfd_, SHUT_WR);
}

void Socket::setReusePort(bool on)
{
	int opt = on ? 1 : 0;
	setsockopt(sockfd_,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
}

void Socket::setReuseAddr(bool on)
{
	int opt = on ? 1 : 0;
	setsockopt(sockfd_,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
}

void Socket::setTcpNoDelay(bool on)
{
	int opt = on ? 1 : 0;
	setsockopt(sockfd_,SOL_SOCKET,TCP_NODELAY,&opt,sizeof(opt));
}

void Socket::setKeepAlive(bool on)
{
	int opt = on ? 1 : 0;
	setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE,&opt, sizeof(opt));
}

ssize_t Socket::write(void *buf, size_t count)
{
	encrypt_msg((char*)buf,count);
	return ::write(sockfd_, buf, count);
}

ssize_t Socket::writen(void *vptr,size_t n)
{
	encrypt_msg((char*)vptr,n);
	size_t nwrite;
	size_t nleft;
	nwrite = 0;
	nleft = n;
	char *ptr = (char*)vptr;
	while(nleft > 0)
	{
		if((nwrite = ::write(sockfd_,ptr,nleft)) <= 0)
		{
			if(nwrite < 0 && errno == EINTR)
				continue;
			else
				return -1;
		}
		nleft -= nwrite;
		ptr += nwrite;
	}
	return (n - nleft);
}

ssize_t Socket::read(void *buf,size_t count)
{
	decrypt_msg((char*)buf,count);
	return ::read(sockfd_,buf,count);
}

ssize_t Socket::readn(void *vptr,size_t n)
{
	decrypt_msg((char*)vptr,n);
	size_t nread;
	size_t nleft;
	nread = 0;
	nleft = n;
	char *ptr = (char*)vptr;
	while(nleft > 0)
	{
		if((nread = ::read(sockfd_,ptr,nleft)) < 0)
		{
			if(errno == EINTR)
				continue;
			else
				return -1;
		}
		else if(nread == 0)
		{
			break;
		}
		nleft -= nread;
		ptr += nread;
	}
	return (n - nleft);
}
