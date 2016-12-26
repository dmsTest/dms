#include "log_queue.h"
#include <algorithm>

LogQueue::LogQueue()
{
    pthread_mutex_init(&m_mutex,NULL);
    pthread_cond_init(&m_cond,NULL);
    //ctor
    //pthread_mutex_t m_mutex;
    //pthread_cond_t m_cond;
}

LogQueue& LogQueue::push(int conn,Msg &log)
{
    //add mutex
    // std::cout << "-------push queue-------" << std::endl;
    int s = pthread_mutex_lock(&m_mutex);
    if(s != 0)
        errExitEN(s,"pthread_mutex_lock");
    //
    m_logs.insert(std::make_pair(conn,log));
    usleep(1000);
    s = pthread_mutex_unlock(&m_mutex);
   // std::cout << "--------push queue end------" << std::endl;
    if(s != 0)
        errExitEN(s,"pthread_mutex_unlock");
    s = pthread_cond_signal(&m_cond);
    if(s != 0)
        errExitEN(s, "pthread_cond_signal");
    return *this;
}

LogQueue& LogQueue::pop(std::pair<int,Msg> &log)
{
    //add mutex
    int s = pthread_mutex_lock(&m_mutex);
    if(s != 0)
        errExitEN(s,"pthread_mutex_lock");
    while(m_logs.empty())
    {
	// std::cout << "-------wait------ " << std::endl;
        s = pthread_cond_wait(&m_cond,&m_mutex);
        if(s != 0)
        {
	//	std::cout << "---------s!=0------" <<std::endl;
            errExitEN(s,"pthread_cond_wait");
        }
    }
    log = *(m_logs.begin());
    m_logs.erase(m_logs.begin());
    usleep(1000);
    s = pthread_mutex_unlock(&m_mutex);
   // std::cout << "--------pop queue-------" << std::endl;
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
