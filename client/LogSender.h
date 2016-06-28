#ifndef LOGSENDER_H
#define LOGSENDER_H

#include <list>
#include <string>
#include "data.h"

class LogSender
{
    public:
        LogSender();
        virtual ~LogSender();
        virtual void sendLog(std::list<MLogRec> &logs) = 0;
};

class ConsoleSender : public LogSender
{
    public:
        void sendLog(std::list<MLogRec> &logs);
        ConsoleSender() : LogSender() {         }
        ~ConsoleSender(){       }
};

class SocketSender : public LogSender
{
    public:
        SocketSender(const std::string &failFile, short port,const std::string &ip);
        void sendLog(std::list<MLogRec> &logs) ;
        void connectServer();
        void readFailFile(std::list<MLogRec>& logs);
        void sendData(std::list<MLogRec>& logs);
        void saveFailFile(std::list<MLogRec>& logs);
    private:
            std::string m_failFile;
            short m_port;
            std::string m_ip;
            int m_sockfd;
};

#endif // LOGSENDER_H
