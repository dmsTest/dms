#include "Client.h"

Client::Client(LogReader& reader,LogSender& sender)
            : m_reader(reader), m_sender(sender)
{

}

void Client::dataMine()
{

}

Client::~Client()
{
    //dtor
}
