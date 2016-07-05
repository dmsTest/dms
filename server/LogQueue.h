#ifndef LOGQUEUE_H
#define LOGQUEUE_H

#include <list>
#include "data.h"
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#define errExitEN(en, msg) \
            do { errno = en; perror(msg); exit(EXIT_FAILURE); \
        } while (0)

class LogQueue
{
public:
    LogQueue();
    LogQueue& push(const MLogRec &log);//push back
    LogQueue& pop(MLogRec &log);//pop front
    virtual ~LogQueue();
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
    std::list<MLogRec> m_logs;
};

#endif // LOGQUEUE_H
