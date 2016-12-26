#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include "log_reader.h"
#include "log_sender.h"
#include "client_log.h"
#include "singleton.h"

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
