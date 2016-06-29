#include "Client.h"

Client::Client(LogReader& reader,LogSender& sender)
            : m_reader(reader), m_sender(sender)
{

}

void Client::dataMine() throw(ClientException)
{
	std::cout << "dms is start..." << std::endl;
	std::list logList<MLogRec> = m_reader.readLog();
	m_reader.backup();
	m_reader.readLoginsFile();
	m_reader.readBackupFile();
	m_reader.match();
	m_reader.saveLoginsFile();
	m_sender.sendLog(logList);
	std::cout << "dms is end..." << std::endl;
}

Client::~Client()
{
    //dtor
}
