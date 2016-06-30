#include "LogReader.h"

LogReader::LogReader(const std::string &logFile, const std::string &loginFile)
                    : m_logFile(logFile),m_loginsFile(loginFile)
{
	MLogRec item = {};
	item.logname = "tanligao";
	item.logip = "127.0.0.1";
	item.pid = 12345;
	item.logintime = 10000;
	item.logouttime = 10020;
	item.logtime = 20;
	m_logs.push_back(item);
}

std::list<MLogRec>&  LogReader::readLog()
{
	backup();
	readLoginsFile();
	readBackupFile();
	match();
	saveLoginsFile();
	return m_logs;
}

void LogReader::backup() throw(BackupException)
{

}

void LogReader::readLoginsFile() throw(ReadException)
{

}

void LogReader::readBackupFile() throw(BackupException)
{

}

void LogReader::match() throw(SocketException)
{

}

void LogReader::saveLoginsFile() throw(SaveException)
{

}

LogReader::~LogReader()
{
    //dtor
}
