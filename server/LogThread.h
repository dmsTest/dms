#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <string>
#include "LogDao.h"
#include "data.h"
#include "ServerException.h"

class LogThread
{
    public:
        LogThread();
        void start();
        virtual void run() = 0 throw(ThreadException);
        virtual ~LogThread();
    private:
        static void* run(void* arg);
};

class ClientThread : public LogThread
{
    public:
        ClientThread();
        ClientThread(int connfd);
        ~ClientThread();
        void run() throw(ThreadException);
    private:
            int m_connfd;
};

class StoreThread : public LogThread
{
    public:
        StoreThread(LogDao &dao);
        ~StoreThread();
        void run() throw(ThreadException);
    private:
        LogDao& m_dao;
};
#endif // LOGTHREAD_H
