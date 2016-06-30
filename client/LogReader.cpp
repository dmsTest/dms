#include "LogReader.h"
#include <fstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <cstring>
#include <time.h>
#include <arpa/inet.h>

using namespace std;
LogReader::LogReader(const std::string &logFile, const std::string &loginFile): m_logFile(logFile)
    ,m_loginsFile(loginFile),m_backupFile(getWtmpxString())
{
}

list<MLogRec>&  LogReader::readLog()  //读取登录日志文件并将读取信息保存至list中
{
    backup();         //调用备份函数进行文件备份
    readLoginsFile(); //读取上次未匹配记录文件
    readBackupFile(); //读取日志记录的备份文件
    match();          //开始登入登出记录匹配
    saveLoginsFile(); //将未匹配的记录保存在文件中
    return m_logs;
}

void LogReader::backup() throw(BackupException)
{
    string str="./backup "+backup;
    system(str.c_str);//调用Linux下的shell脚本文件 进行日志记录wtmpx文件备份
}

void LogReader::readBackupFile() throw(BackupException)   //读取备份的日志文件
{
    unsigned type=0;//用于判断是登入还是登出
    fstream fin;
    fin.open(m_backupFile.c_str(),ios::binary|ios::in);
    if(!fin.is_open())
    {
        cout<<"open file faile!"<<endl;

    }
    fin.seekg(0,ios::end);
    int fsize = fin.tellg()/372;  //算出备份的日志文件中的登入登出记录数目
    fin.seekg(0,ios::beg);
    cout<<"start read backupFile!"<<endl;
    for(int i=0; i<fsize; i++)
    {
        int login_num,logout_num;
        login_num=logout_num=0;
        LogRec logrec;
        int  pos=i*372;         //设定文件指针每次读取记录时的位置，每次读取都在一条记录的开始处
        fin.seekg(pos,ios::beg);
        fin.read((char*)&(logrec.logname),sizeof(logrec.logname));  //读取登录记录的登录名
        if(logrec.logname[0]!='.')//判断是否为收费用户的记录
        {
            fin.seekg(pos+68,ios::beg);  //将文件指针指向第n条记录的登录id位置
            fin.read((char*)&(logrec.pid),sizeof(logrec.pid));//读取登录id
            logrec.pid=htonl(logrec.pid);//将数据有网络序转换成主机序
            fin.seekg(72+pos,ios::beg);  //原理同上
            fin.read((char*)&type,sizeof(type));
            type = htons(type);
            fin.seekg(80+pos,ios::beg);
            fin.read((char*)&(logrec.logtime),sizeof(logrec.logtime));
            logrec.logtime = htonl(logrec.logtime);
            fin.seekg(114+pos,ios::beg);
            fin.read((char*)&(logrec.logip),sizeof(logrec.logip));
            if(type==7)          //如果是7则可以判定是登入记录 把记录写入登入list
            {
                m_logins.push_back(logrec);
                lonin_num++;

            }
            else if(type==8)    //如果是8则可以判定是登入记录 把记录写入登出list
            {
                m_logouts.push_back(logrec);
                logout_num++;
            }
        }
    }
    fin.close();  //关闭文件流
    cout<<"end read backupFile!"<<endl;
}
//获取备份文件名 构造函数中调用初始化m_logFile变量
std::string LogReader::getWtmpxString()
{
    time_t now_time;
    time(&now_time);
    struct tm *now_tm;
    now_tm = localtime(&now_time);
    char wtmpxFile[20];
    sprintf(wtmpxFile,"%s.%04d%02d%02d%02d%02d%02d",m_logFile.c_str(),now_tm->tm_year+1900,now_tm->tm_mon+1,now_tm->tm_mday,now_tm->tm_hour,now_tm->tm_min,now_tm->tm_sec);
    std::string str(wtmpxFile);
    //std::cout << str << std::endl;
    return str;
}

void LogReader::readLoginsFile() throw(ReadException) //读取上次未匹配成功的信息文件
{
    fstream fin;
    fin.open(m_loginsFile.c_str(),ios::binary|ios::in); //以二进制写的方式打开m_loginsFile文件
    if(!fin.is_open())
    {
        cerr<<"Read LoginsFile error!"<<endl;
    }
    fin.seekg(0,ios::end);
    int fsize = fin.tellg()/372;
    cout<<"共有"<<fsize<<"条未匹配记录！"<<endl;
    fin.seekg(0,ios::beg);
    cout<<"start read unsuccessful match data!"<<endl;
    for(int i=0; i<fsize; i++)
    {
        LogRec logrec;
        int  pos=i*372;    //文件中每条记录的开始位置
        fin.seekg(pos,ios::beg);//将文件指针指向一条记录的开始位置
        fin.read((char*)&(logrec.logname),sizeof(logrec.logname));//读取记录中登录名
        fin.seekg(pos+68,ios::beg); //将文件指针跳过68字节，指向登录id的信息位置
        fin.read((char*)&(logrec.pid),sizeof(logrec.pid));//读取id
        fin.seekg(80+pos,ios::beg);//原理同上
        fin.read((char*)&(logrec.logtime),sizeof(logrec.logtime));
        fin.seekg(114+pos,ios::beg);
        fin.read((char*)&(logrec.logip),sizeof(logrec.logip));
        m_logins.push_back(logrec);                   //将读取的未匹配记录插入登入记录list
    }
    fin.close();
    cout<<"end read unsuccessful match data!"<<endl;
}

void LogReader::match() throw(SocketException)              //匹配登入登出数据
{
    cout<<"start match login and logout data!"<<endl;
    list<LogRec>::iterator init;   //指向记录登入信息list的迭代器
    list<LogRec>::iterator outit;  //指向记录登入信息list的迭代器
    for(outit=m_logouts.begin(); outit!=m_logouts.end(); outit++)  //双重循环 用登入记录和登出记录逐条比对
    {
        for(init=m_logins.begin(); init!=m_logins.end(); init++)
        {
            if(strcmp(outit->logname,init->logname)==0
                    &&strcmp(outit->logip,init->logip)==0&&
                    outit->pid==init->pid&&outit->logtime>init->logtime) //if条件成立则匹配成功 把数据写入匹配成功list 切记登入时间必定小于登出时间
            {
                MLogRec mlogrec;
                strcpy(mlogrec.logname,outit->logname);
                strcpy(mlogrec.logip,outit->logip);
                mlogrec.pid=outit->pid;
                mlogrec.logintime=init->logtime;
                mlogrec.logouttime=outit->logtime;
                mlogrec.logtime=outit->logtime-init->logtime;
                m_logs.push_back(mlogrec);
                init=m_logins.erase(init);         //将匹配完成的登入记录从m_logins登入记录表中删除
            }
        }
        outit=m_logouts.erase(outit);             //将匹配完成的登出记录从m_logouts登出记录表中删除
    }
    cout<<"mogin and logout data over!"<<endl;
}

void LogReader::saveLoginsFile() throw(SaveException)       //将未匹配成功的记录保存
{
    fstream fout;
    fout.open(m_loginsFile.c_str(),ios::binary|ios::out|ios::app);
    if(!fout.is_open())
    {
        throw SaveException("open last time unsuccessful match data faile!");
    }
    int count = m_logins.size();
    int logrec_size=sizeof(LogRec);
    list<LogRec>::iterator init;
    for(init=m_logins.begin(); init!=m_logins.end(); init++)
    {
        fout.write((char*)(&(*init)),logrec_size);
    }
    fout.close();
    cout<<"write unsuccessful match data over!total"<<count<<"unmatched data"<<endl;
}

LogReader::~LogReader()
{

}
