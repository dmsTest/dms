#ifndef LOGSENDER_H
#define LOGSENDER_H

#include <list>
#include <string>
#include "data.h"
#include "ClientException.h"

class LogSender
{
    public:
        LogSender();
        virtual ~LogSender();
        virtual void sendLog(std::list<MLogRec> &logs) throw(SendException) = 0;
};

class ConsoleSender : public LogSender
{
    public:
        void sendLog(std::list<MLogRec> &logs)throw(SendException);
        ConsoleSender() : LogSender() {         }
        ~ConsoleSender(){       }
};

class SocketSender : public LogSender
{
    public:
        SocketSender(const std::string &failFile, short port,const std::string &ip);
        void sendLog(std::list<MLogRec> &logs) throw(SendException);
        void connectServer();
        void readFailFile(std::list<MLogRec>& logs) throw(ReadException);
        void sendData(std::list<MLogRec>& logs) throw(SendException);
        void saveFailFile(std::list<MLogRec>& logs) throw(SaveException);
    private:
        std::string m_failFile;
        short m_port;
        std::string m_ip;
        int m_sockfd;
};

#endif // LOGSENDER_H
