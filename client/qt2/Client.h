#ifndef CLIENT_H
#define CLIENT_H

#include "LogReader.h"
#include "LogSender.h"
#include <iostream>

class Client
{
    public:
        Client(LogReader& reader,LogSender& sender);
        void dataMine() throw(ClientException);
        virtual ~Client();
        //list<MLogRec>& getloglist();   //////
    private:
        LogReader& m_reader;
        LogSender& m_sender;
        list<MLogRec> loglist; /////
};

#endif // CLIENT_H
