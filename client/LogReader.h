#ifndef LOGREADER_H
#define LOGREADER_H

#include <string>
#include <iostream>
#include <list>
#include "data.h"
#include "ClientException.h"


class LogReader
{
    public:
        LogReader(const std::string &logFile, const std::string &loginFile);
         std::list<MLogRec>&  readLog() ;
        virtual ~LogReader();

    private:
        std::string m_logFile;
        std::string m_loginsFile;
        std::string m_backupFile;
        std::list<LogRec> m_logins;
        std::list<LogRec> m_logouts;
        std::list<MLogRec> m_logs;

        void backup() throw(BackupException);
        void readLoginsFile() throw(ReadException);
        void readBackupFile() throw(BackupException);
        void match() throw(SocketException);
        void saveLoginsFile() throw(SaveException);
};

#endif // LOGREADER_H
