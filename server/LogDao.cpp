#include "LogDao.h"

LogDao::LogDao()
{
    //ctor
}

LogDao::~LogDao()
{
    //dtor
}

FileDao::FileDao(const std::string& path) : m_ofs(path)
{

}

FileDao::~FileDao()
{

}

void FileDao::insert(const MLogRec& log) throw(DBException)
{

}

MysqlDao::MysqlDao(const std::string &username, const std::string &password)
{

}

MysqlDao::~MysqlDao()
{

}

void MysqlDao::insert(const MLogRec& log) throw(DBException)
{

}
