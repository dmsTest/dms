#include "LogSender.h"

LogSender::LogSender()
{
    //ctor
}

LogSender::~LogSender()
{
    //dtor
}

void ConsoleSender::sendLog(std::list<MLogRec> &logs) throw(SendException("console")
{
	
}

SocketSender::SocketSender(const std::string &failFile, short port,const std::string &ip,int &sockfd)
	:m_failFile(failFile),m_port(port),m_ip(ip)
{
	
}

void SocketSender::sendLog(std::list<MLogRec> &logs) throw(SocketException)
{
	

}

void SocketSender::connectServer()
{
	

}

void SocketSender::readFailFile(std::list<MLogRec>& logs) throw(ReadException)
{
	

}

void SocketSender::sendData(std::list<MLogRec>& logs) throw(SendException)
{
	

}
     
void SocketSender::saveFailFile(std::list<MLogRec>& logs) throw(SaveException)
{
	

}

