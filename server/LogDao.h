#ifndef LOGDAO_H
#define LOGDAO_H

#include <iostream>
#include <string>
#include <fstream>
#include "data.h"
#include "ServerException.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class LogDao
{
    public:
        LogDao();
        virtual void insert(const MLogRec& log) throw(DBException) = 0;
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
        void insert(const MLogRec& log) throw(DBException);
    private:
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement *pstmt;
};

#endif // LOGDAO_H
