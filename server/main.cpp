#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "data.h"
#include "LogDao.h"

using namespace std;

short _port = 8888;
string _ip = "127.0.0.1";

/*
void* task(void* arg)
{
    int fd = *(int*)arg;
    while(1)
    {
        //7. 接收数据
        char buf[96];
        recv(fd, buf, sizeof(buf), 0);
        //cout << sizeof(MLogRec) << endl;
        //printf("%s\n", buf);
        if(!strcmp(buf, "BYE"))
            break;
        MLogRec item;
        memcpy(&item,buf,sizeof(buf));
        std::cout << "logname: " << item.logname <<
                  ", logip: " << item.logip <<
                  ", pid: " << item.pid <<
                  ", logintime: " << item.logintime <<
                  ", logouttime: " << item.logouttime <<
                  ", logtime: " << item.logtime << std::endl;
    }
    //8. 关闭描述符
    close(fd);
    return NULL;
}
*/
int main(int argc, char **argv)
{
    /*
    // 1.获取socket描述
    int sockfd = socket(AF_INET,
                        SOCK_STREAM, 0);
    if(-1 == sockfd)
    {
        perror("socket");
        return -1;
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
        return -2;
    }
    printf("bind ok!\n");
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
            pthread_t tid;
            pthread_create(&tid, NULL, task, &fd);
        }
    }
    //9. 关闭描述符
    close(sockfd);
    */
    MysqlDao sqlDao("root","");
    Server server(sqlDao, _port, _ip);
    server.dataMine();
    return 0;
}
