#ifndef CLIENT_H
#define CLIENT_H

#include "LogReader.h"
#include "LogSender.h"

class Client
{
    public:
        Client(LogReader& reader,LogSender& sender);
        void dataMine() throw(ClientException);
        virtual ~Client();
    private:
        LogReader& m_reader;
        LogSender& m_sender;
};

#endif // CLIENT_H
