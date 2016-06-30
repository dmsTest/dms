#include "Client.h"

Client::Client(LogReader& reader,LogSender& sender)
            : m_reader(reader), m_sender(sender)
{

}

void Client::dataMine() throw(ClientException)
{
	std::cout << "dms is start..." << std::endl;
	std::list<MLogRec> logList = m_reader.readLog();
	std::cout << logList.size() << std::endl;
	m_sender.sendLog(logList);
	std::cout << "dms is end..." << std::endl;
}

Client::~Client()
{
    //dtor
}
