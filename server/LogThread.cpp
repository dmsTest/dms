#include "LogThread.h"
#include <cstdio.h>
#include <cstring>
#include <unistd.h>
#include <list>
#include "LogQueue.h"

LogThread::LogThread()
{
    //ctor
}

void LogThread::start()
{
    pthread_t tid;
    int error=pthread_creat(&tid,NULL,run,this);
    if(error)
    {
        printf("%s\n",strerror(tid));
    }
    run();
}

void* LogThread::run(void* arg)
{
    static_cast<Thread*>(arg)->run();
    
}

LogThread::~LogThread()
{
    //dtor
}

ClientThread::ClientThread() : LogThread()       //ClientThread的构造函数
{

}

ClientThread::ClientThread(int connfd) : LogThread(), m_connfd(connfd)
{

}


void ClientThread::run() throw(ThreadException)
{
    while(1)
    {
        //7. 接收数据
        char buf[sizeof(MLogRec)];
        recv(m_connfd, buf, sizeof(buf), 0);
        MLogRec item;
        memcpy(&item,buf,sizeof(buf));
        logqueue.push(item);
    }
}

ClientThread::~ClientThread()
{

}

StoreThread::StoreThread(LogDao& dao) : LogThread(),m_dao(dao)   //StoreThread的构造函数
{

}

StoreThread::~StoreThread()
{

}

void StoreThread::run() throw(ThreadException)
{
	list<MLogRec>::iterator it;
        MLogRec mlogrec;
	for(it=logqueue.mlogs.begin();it!=logqueue.mlogs.end(),it++){
            logqueue.pop(mlogrec);
	    dao.insert(mlogrec);
	}
}
