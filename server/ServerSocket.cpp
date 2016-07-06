#include "ServerSocket.h"


ServerSocket::ServerSocket(short port, const std::string ip)
{
// 1.获取socket描述
    m_sockfd = socket(AF_INET,
                        SOCK_STREAM, 0);
    if(-1 == m_sockfd)
    {
        perror("socket");
        return;
    }
    // 2.准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr =
        inet_addr("127.0.0.1");
    //3.绑定IP地址
    int ret = bind(m_sockfd,
                   (struct sockaddr*)&addr,
                   sizeof(addr));
    if(-1 == ret)
    {
        perror("bind");
        return;
    }
    printf("bind ok!\n");
    std::cout << "-------start listen--------" << std::endl;
    //4.监听
    listen(m_sockfd, 100);
    std::cout << "-------listen----------" << std::endl;
}

void ServerSocket::acceptClient() throw(SocketException)
{
    std::cout << "-------accept----------" << std::endl;
    while(1)
    {
        struct sockaddr_in from;
        socklen_t len = sizeof(from);
        while(1)
        {
            // 5.接收来接收客户端连接
            int fd = accept(m_sockfd,
                            (struct sockaddr*)&from,
                            (socklen_t*)&len);
            //6.创建线程，接收来自客户端的数据
            //pthread_t tid;
            //pthread_create(&tid, NULL, task, &fd);
	    if(fd != -1)
	    {    
		    std::cout << "------client arrive------" << std::endl;
            	(new ClientThread(fd))->start();
	    }
        }
    }
}

ServerSocket::~ServerSocket()
{
    //dtor
    //9. 关闭描述符
    close(m_sockfd);
}
