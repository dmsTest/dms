#include "client.h"

Client::Client(LogReader& reader,LogSender& sender)
            : m_reader(reader), m_sender(sender)
{

}

void Client::dataMine() throw(ClientException)
{
	Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------dms is start-----");
	std::list<MLogRec> logList = m_reader.readLog();
	std::cout << logList.size() << std::endl;
	m_sender.sendLog(logList);
	Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------dms is end-----");
}

Client::~Client()
{
    //dtor
}
