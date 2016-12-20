#ifndef LOGSENDER_H
#define LOGSENDER_H

#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <string.h>
#include "data.h"
#include "ClientException.h"
#include "Log.h"

#define WAIT_SEC 5

class LogSender
{
    public:
        LogSender(){};
        virtual ~LogSender(){};
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
        ~SocketSender();
        void sendLog(std::list<MLogRec> &logs) throw(SendException);
        void connectServer();
        void readFailFile(std::list<MLogRec>& logs) throw(ReadException);
        bool sendData(Msg &msg) throw(SendException);
        void saveFailFile(std::list<MLogRec>& logs) throw(SaveException);
        bool is_register();
        bool is_login();
    private:
        std::string m_failFile;
        short m_port;
        std::string m_ip;
        int m_sockfd;
        bool is_closed;
};

template<typename T>
std::string converTToString(T value)
{
    std::stringstream ss;
    ss << value;
    std::string str = ss.str();
    return str;
}
#endif // LOGSENDER_H
