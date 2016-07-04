#include "LogThread.h"

LogThread::LogThread()
{
    //ctor
}

void LogThread::start()
{
    run();
}

void* LogThread::run(void* arg)
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

        //then,insert to mysql
        std::cout << "logname: " << item.logname <<
                  ", logip: " << item.logip <<
                  ", pid: " << item.pid <<
                  ", logintime: " << item.logintime <<
                  ", logouttime: " << item.logouttime <<
                  ", logtime: " << item.logtime << std::endl;
    }
}

LogThread::~LogThread()
{
    //dtor
}

ClientThread::ClientThread() : LogThread()
{

}

ClientThread::ClientThread(int connfd) : LogThread(), m_connfd(connfd)
{

}


void ClientThread::run() throw(ThreadException)
{

}

ClientThread::~ClientThread()
{

}

StoreThread::StoreThread(LogDao& dao) : LogThread(),m_dao(dao)
{

}

StoreThread::~StoreThread()
{

}

void StoreThread::run() throw(ThreadException)
{

}
