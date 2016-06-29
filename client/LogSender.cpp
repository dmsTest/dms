#include "LogSender.h"

LogSender::LogSender()
{
    //ctor
}

LogSender::~LogSender()
{
    //dtor
}

void ConsoleSender::sendLog(std::list<MLogRec> &logs)throw(SendException)
{
	
}

SocketSender::SocketSender(const std::string &failFile, short port,const std::string &ip)
	:m_failFile(failFile),m_port(port),m_ip(ip)
{
	
}

void SocketSender::sendLog(std::list<MLogRec> &logs) throw(SendException)
{
	readFailFile(logs);
	connectServer();
	sendData(logs);
	saveFailFile(logs);
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

