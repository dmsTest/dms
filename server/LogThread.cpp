#include "LogThread.h"

LogThread::LogThread()
{
    //ctor
}

void LogThread::start()
{

}

void LogThread::run(void* arg)
{

}

LogThread::~LogThread()
{
    //dtor
}

ClientThread::ClientThread()
{

}

ClientThread::ClientThread(int connfd) : LogThread(), m_connfd(connfd)
{

}


void ClientThread::run()
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

void StoreThread::run()
{

}
