#include "ServerSocket.h"


ServerSocket::ServerSocket(short port, const std::string ip)
{
// 1.获取socket描述
    m_sockfd = socket(AF_INET,
                        SOCK_STREAM, 0);
    if(-1 == sockfd)
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
    int ret = bind(sockfd,
                   (struct sockaddr*)&addr,
                   sizeof(addr));
    if(-1 == ret)
    {
        perror("bind");
        return;
    }
    printf("bind ok!\n");

}

void ServerSocket::acceptClient() throw(SocketException)
{
      //4.监听
    listen(sockfd, 100);
    while(1)
    {
        struct sockaddr_in from;
        socklen_t len = sizeof(from);
        while(1)
        {
            // 5.接收来接收客户端连接
            int fd = accept(sockfd,
                            (struct sockaddr*)&from,
                            (socklen_t*)&len);
            //6.创建线程，接收来自客户端的数据
            //pthread_t tid;
            //pthread_create(&tid, NULL, task, &fd);
            ClientThread clientThread(fd);
            clientThread.start();
        }
    }
}

ServerSocket::~ServerSocket()
{
    //dtor
    //9. 关闭描述符
    close(sockfd);
}
