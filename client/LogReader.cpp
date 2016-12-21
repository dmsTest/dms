#include "LogReader.h"
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <time.h>
#include <arpa/inet.h>
#include "data.h"
#include "Log.h"
                                    
using namespace std;

LogReader::LogReader(const std::string &logFile, const std::string &loginFile): m_logFile(logFile)
    ,m_loginsFile(loginFile)
{
	m_backupFile=getWtmpxString();
}

list<MLogRec>&  LogReader::readLog()
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
    string str="./backup "+m_backupFile;
    system(str.c_str());
}

void LogReader::readBackupFile() throw(BackupException)
{
    short type=0;
    wtmpx_data buf_data[BUF_SIZE];                      // use read buffer
    int wtmpx_fd = open(m_backupFile.c_str(), O_RDONLY);
    if( wtmpx_fd < 0 )
    {
        oops("open wtmpx file error",1);
    }
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------begin read wtmpx file---------");
    int read_n;
    int login_num = 0;
    int logout_num = 0;
    while( (read_n = read(wtmpx_fd,buf_data,sizeof(buf_data))) > 0 )
    {
        int n_size;
        n_size = read_n / sizeof(struct wtmpx_data);
        if( n_size < 0 || n_size > BUF_SIZE )
        {
            oops("read wtmpx file error",1);
        }
        for( int i = 0; i < n_size; ++i )
        {
            type = htons(buf_data[i].login_type);
            if( type == LOGIN || type == LOGOUT )
            {
                LogRec *p_item = new LogRec();
                strncpy(p_item->logname,buf_data[i].user_name,sizeof(p_item->logname));
                strncpy(p_item->logip,buf_data[i].login_ip,sizeof(p_item->logip));
                p_item->pid = htonl(buf_data[i].login_pid);
                p_item->logtime = buf_data[i].login_sec;
                if( type == LOGIN )
                {
                    m_logins.push_back(p_item);    
                    ++login_num;
                }
                else
                {
                    pair<string,long> item = make_pair(p_item->getString(),p_item->logtime);
                    delete p_item;
                    m_logouts.insert(item);
                    ++logout_num;
                }
            }
        }        
    }
    close(wtmpx_fd);
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s%d\n","---------loginFile size:---------",m_logins.size());
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s%d\n","---------logoutFile size:---------",m_logouts.size());
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------end read wtmpx backup file---------");
}

std::string LogReader::getWtmpxString()
{
    time_t now_time;
    time(&now_time);
    struct tm *now_tm;
    now_tm = localtime(&now_time);
    char wtmpxFile[20];
    sprintf(wtmpxFile,"%s.%04d%02d%02d%02d%02d%02d",m_logFile.c_str(),now_tm->tm_year+1900,now_tm->tm_mon+1,now_tm->tm_mday,now_tm->tm_hour,now_tm->tm_min,now_tm->tm_sec);
    std::string str(wtmpxFile);
    return str;
}

void LogReader::readLoginsFile() throw(ReadException)
{
    int login_fd = open(m_loginsFile.c_str(), O_RDONLY);
    if( login_fd < 0 )
    {
        oops("open login file error",1);
    }
    LogRec buf_data[BUF_SIZE];
    int n_read;
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------begin read login file---------");
    while( (n_read = (read(login_fd,buf_data,sizeof(LogRec) * BUF_SIZE))) > 0 )
    {
        int n_size = n_read / sizeof(LogRec);
        for( int i = 0; i < n_size; ++i )
        {
            LogRec *p_item = new LogRec(buf_data[i]);
            m_logins.push_back(p_item);
        }
    }
    close(login_fd);
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s%d%s\n","------------read ",m_logins.size()," records------------");
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------end read login file---------");
}

void LogReader::match() throw(SocketException)
{
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------start match login data with logout data---------");
    list<LogRec*>::iterator init = m_logins.begin();
    while(init != m_logins.end())
    {
        LogRec *item = *init;
        string init_str = item->getString();
        multimap<string,long>::iterator find_it = m_logouts.find(init_str);
        if(find_it != m_logouts.end())
        {
            MLogRec mlogrec;
            extern std::string g_username;
            strcpy(mlogrec.username,g_username.c_str());
            strcpy(mlogrec.logname,item->logname);
            strcpy(mlogrec.logip,item->logip);
            mlogrec.pid = item->pid;
            mlogrec.logintime = item->logtime;
            mlogrec.logouttime = find_it->second;
            mlogrec.logtime = find_it->second - item->logtime;
            m_logs.push_back(mlogrec);    
            m_logouts.erase(find_it);
            delete item;
            init = m_logins.erase(init);
        }
        else
        {
            ++init;
        }
    }
    m_logouts.clear();                              //清空map
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"---------total matched: %d---------\n",m_logs.size());
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------match login with logout over---------");
}

void LogReader::saveLoginsFile() throw(SaveException)
{
    if( m_logins.empty())
        return;

    int login_fd = open(m_loginsFile.c_str(), O_WRONLY | O_CREAT);
    if( login_fd < 0 )
    {
        oops("open login file error",1);
    }
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------begin save login file---------");
    list<LogRec*>::iterator init;
    for(init=m_logins.begin(); init!=m_logins.end(); init++)
    {
        LogRec *item = *init;
        write(login_fd, item, sizeof(*item));
    }
    close(login_fd);
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"---------save %d records-----------\n",m_logins.size());
    Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","end save login file");
}

LogReader::~LogReader()
{
    while( !m_logins.empty() )
    {
        LogRec* p_item = m_logins.front();
        m_logins.pop_front();
        delete p_item;
    }
    if( !m_logouts.empty() )
        m_logouts.clear();
}
