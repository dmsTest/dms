#ifndef LOGQUEUE_H
#define LOGQUEUE_H

#include <map>
#include "data.h"
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#define errExitEN(en, msg) \
            do { errno = en; perror(msg); exit(EXIT_FAILURE); \
        } while (0)

class LogQueue
{
public:
    LogQueue();
    LogQueue& push(int conn,Msg &log);//push back
    LogQueue& pop(std::pair<int,Msg> &log);//pop front
    virtual ~LogQueue();
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
    std::multimap<int,Msg> m_logs;
};

#endif // LOGQUEUE_H
