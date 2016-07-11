#ifndef LOGREADER_H
#define LOGREADER_H

#include <string>
#include <iostream>
#include <list>
#include <map>
#include <utility>
#include "data.h"
#include "ClientException.h"

using namespace std;

class LogReader
{
public:
    LogReader(const string &logFile, const string &loginFile);    //¹¹Ôìº¯Êý µÇÂ¼¼ÇÂ¼
    list<MLogRec>& readLog();
    virtual ~LogReader();


private:
    string m_logFile;         //原始日志记录文件
    string m_loginsFile;      //未匹配的日志记录文件
    string m_backupFile;      //备份的日志记录文件
    list<LogRec> m_logins;    //登入记录表
    multimap<string,long> m_logouts;   //登出记录表,key为logname+logip+pid,value为logtime
    list<MLogRec> m_logs;     //匹配成功的日志记录表

    void backup() throw(BackupException);  //备份日志记录
    void readLoginsFile() throw(ReadException); //读取匹配未成功的记录文件
    void readBackupFile() throw(BackupException); //读取日志记录的备份文件
    void match() throw(SocketException);  //匹配登入登出记录
    void saveLoginsFile() throw(SaveException); //存储将未匹配的登入记录保存
    std::string getWtmpxString();//logFile转换成backupFile
};

#endif // LOGREADER_H
