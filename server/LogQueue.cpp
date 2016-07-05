#include "LogQueue.h"
#include <algorithm>

LogQueue::LogQueue()
{
    pthread_mutex_init(&m_mutex,NULL);
    pthread_cond_init(&m_cond,NULL);
    //ctor
    //pthread_mutex_t m_mutex;
    //pthread_cond_t m_cond;
}

LogQueue& LogQueue::push(const MLogRec &log)
{
    //add mutex
    int s = pthread_mutex_lock(&m_mutex);
    if(s != 0)
        errExitEN(s,"pthread_mutex_lock");
    m_logs.push_back(log);
    s = pthread_mutex_unlock(&m_mutex);
    if(s != 0)
        errExitEN(s,"pthread_mutex_unlock");
    s = pthread_cond_signal(&m_cond);
    if(s != 0)
        errExitEN(s, "pthread_cond_signal");
    return *this;
}

LogQueue& LogQueue::pop(MLogRec &log)
{
    //add mutex
    int s = pthread_mutex_lock(&m_mutex);
    if(s != 0)
        errExitEN(s,"pthread_mutex_lock");
    while(m_logs.empty())
    {
        s = pthread_cond_wait(&m_cond,&m_mutex);
        if(s != 0)
        {
            errExitEN(s,"pthread_cond_wait");
        }
    }
    log= m_logs.front();
    m_logs.pop_front();
    s = pthread_mutex_unlock(&m_mutex);
    if(s != 0)
        errExitEN(s,"pthread_mutex_unlock");
    return *this;
}

LogQueue::~LogQueue()
{
    //dtor
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);
}
