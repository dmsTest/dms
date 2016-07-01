#include "LogQueue.h"
#include <algorithm>

LogQueue::LogQueue()
{
    //ctor
}

 LogQueue& LogQueue::operator<<(const MLogRec &log)
 {
    std::list<MLogRec>::iterator it_pos = find(m_logs.begin(),m_logs.end(),log);
    it_pos = m_logs.erase(it_pos);
    return *this;
 }

LogQueue& LogQueue::operator>>(MLogRec &log)
{
    m_logs.push_back(log);
    return *this;
}

LogQueue::~LogQueue()
{
    //dtor
}
