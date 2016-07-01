#ifndef LOGQUEUE_H
#define LOGQUEUE_H

#include <list>
#include "data.h"
#include <pthread.h>

class LogQueue
{
    public:
        LogQueue();
        LogQueue& operator<<(const MLogRec &log);
        LogQueue& operator>>(MLogRec &log);
        virtual ~LogQueue();
    private:
        pthread_mutex_t m_mutex;
        pthread_cond_t m_cond;
        std::list<MLogRec> m_logs;
};

#endif // LOGQUEUE_H
