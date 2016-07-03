#ifndef LOGDAO_H
#define LOGDAO_H

#include <string>
#include <fstream>
#include "data.h"

class LogDao
{
    public:
        LogDao();
        virtual void insert(const MLogRec& log) = 0;
        virtual ~LogDao();
};

class FileDao : public LogDao
{
    public:
        FileDao(const std::string& path);
        ~FileDao();
        void insert(const MLogRec& log);
    private:
            std::ofstream m_ofs;
};

class MysqlDao : public LogDao
{
    public:
        MysqlDao(const std::string &username, const std::string &password);
        ~MysqlDao();
        void insert(const MLogRec& log);
};


#endif // LOGDAO_H
