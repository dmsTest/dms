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
#include "client_exception.h"
#include "client_log.h"

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
        SocketSender(const std::string &failFile);
        ~SocketSender();
        void sendLog(std::list<MLogRec> &logs) throw(SendException);
        bool connectServer();
        void readFailFile(std::list<MLogRec>& logs) throw(ReadException);
        bool sendData(MLogRec &send_data) throw(SendException);
        void saveFailFile(std::list<MLogRec>& logs) throw(SaveException);
        bool is_register();
        bool is_login();
    private:
        std::string m_failFile;
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
