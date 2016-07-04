#ifndef LOGDAO_H
#define LOGDAO_H

#include <string>
#include <fstream>
#include "data.h"
#include "ServerException.h"

class LogDao
{
    public:
        LogDao();
        virtual void insert(const MLogRec& log) = 0 throw(DBException);
        virtual ~LogDao();
};

class FileDao : public LogDao
{
    public:
        FileDao(const std::string& path);
        ~FileDao();
        void insert(const MLogRec& log) throw(DBException);
    private:
            std::ofstream m_ofs;
};

class MysqlDao : public LogDao
{
    public:
        MysqlDao(const std::string &username, const std::string &password);
        ~MysqlDao();
        void insert(const MLogRec& log) thro(DBException);
};

#endif // LOGDAO_H
