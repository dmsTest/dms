#include "LogReader.h"

LogReader::LogReader(const std::string &logFile, const std::string &loginFile)
                    : m_logFile(logFile),m_loginsFile(loginFile)
{

}

std::list<MLogRec>&  LogReader::readLog()
{
	backup();
	readLoginsFile();
	readBackupFile();
	match();
	saveLoginsFile();
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
