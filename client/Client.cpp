#include "Client.h"

Client::Client(LogReader& reader,LogSender& sender)
            : m_reader(reader), m_sender(sender)
{

}

void Client::dataMine()
{
	std::list logList<MLogRec> = m_reader.readLog();
	m_reader.backup();
	m_reader.readLoginsFile();
	m_reader.readBackupFile();
	m_reader.match();
	m_reader.saveLoginsFile();
	m_sender.sendLog(logList);
}

Client::~Client()
{
    //dtor
}
