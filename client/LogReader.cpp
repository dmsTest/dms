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

list<MLogRec>&  LogReader::readLog()  //¶ÁÈ¡µÇÂ¼ÈÕÖ¾ÎÄ¼þ²¢½«¶ÁÈ¡ÐÅÏ¢±£´æÖÁlistÖÐ
{
    backup();         //µ÷ÓÃ±¸·Ýº¯Êý½øÐÐÎÄ¼þ±¸·Ý
    readLoginsFile(); //¶ÁÈ¡ÉÏ´ÎÎ´Æ¥Åä¼ÇÂ¼ÎÄ¼þ
    readBackupFile(); //¶ÁÈ¡ÈÕÖ¾¼ÇÂ¼µÄ±¸·ÝÎÄ¼þ
    match();          //¿ªÊ¼µÇÈëµÇ³ö¼ÇÂ¼Æ¥Åä
    saveLoginsFile(); //½«Î´Æ¥ÅäµÄ¼ÇÂ¼±£´æÔÚÎÄ¼þÖÐ
    return m_logs;
}

void LogReader::backup() throw(BackupException)
{
    string str="./backup "+m_backupFile;
    system(str.c_str());//µ÷ÓÃLinuxÏÂµÄshell½Å±¾ÎÄ¼þ ½øÐÐÈÕÖ¾¼ÇÂ¼wtmpxÎÄ¼þ±¸·Ý
}

void LogReader::readBackupFile() throw(BackupException)   //¶ÁÈ¡±¸·ÝµÄÈÕÖ¾ÎÄ¼þ
{
    unsigned type=0;//ÓÃÓÚÅÐ¶ÏÊÇµÇÈë»¹ÊÇµÇ³ö
    fstream fin;
    fin.open(m_backupFile.c_str(),ios::binary|ios::in);
    if(!fin.is_open())
    {
        cout<<"open file faile!"<<endl;

    }
    fin.seekg(0,ios::end);
    int fsize = fin.tellg()/372;  //Ëã³ö±¸·ÝµÄÈÕÖ¾ÎÄ¼þÖÐµÄµÇÈëµÇ³ö¼ÇÂ¼ÊýÄ¿
    fin.seekg(0,ios::beg);
    cout<<"Start read backupFile!"<<endl;
    int login_num,logout_num;
    login_num=logout_num=0;
    for(int i=0; i<fsize; i++)
    {
        LogRec logrec;
        int  pos=i*372;         //Éè¶¨ÎÄ¼þÖ¸ÕëÃ¿´Î¶ÁÈ¡¼ÇÂ¼Ê±µÄÎ»ÖÃ£¬Ã¿´Î¶ÁÈ¡¶¼ÔÚÒ»Ìõ¼ÇÂ¼µÄ¿ªÊ¼´¦
        fin.seekg(pos,ios::beg);
        fin.read((char*)&(logrec.logname),sizeof(logrec.logname));  //¶ÁÈ¡µÇÂ¼¼ÇÂ¼µÄµÇÂ¼Ãû
        if(logrec.logname[0]!='.')//ÅÐ¶ÏÊÇ·ñÎªÊÕ·ÑÓÃ»§µÄ¼ÇÂ¼
        {
            fin.seekg(pos+68,ios::beg);  //½«ÎÄ¼þÖ¸ÕëÖ¸ÏòµÚnÌõ¼ÇÂ¼µÄµÇÂ¼idÎ»ÖÃ
            fin.read((char*)&(logrec.pid),sizeof(logrec.pid));//¶ÁÈ¡µÇÂ¼id
            logrec.pid=htonl(logrec.pid);//½«Êý¾ÝÓÐÍøÂçÐò×ª»»³ÉÖ÷»úÐò
            fin.seekg(72+pos,ios::beg);  //Ô­ÀíÍ¬ÉÏ
            fin.read((char*)&type,sizeof(type));
            type = htons(type);
            fin.seekg(80+pos,ios::beg);
            fin.read((char*)&(logrec.logtime),sizeof(logrec.logtime));
            logrec.logtime = htonl(logrec.logtime);
            fin.seekg(114+pos,ios::beg);
            fin.read((char*)&(logrec.logip),sizeof(logrec.logip));
            if(type==7)          //Èç¹ûÊÇ7Ôò¿ÉÒÔÅÐ¶¨ÊÇµÇÈë¼ÇÂ¼ °Ñ¼ÇÂ¼Ð´ÈëµÇÈëlist
            {
                m_logins.push_back(logrec);
                login_num++;

            }
            else if(type==8)    //Èç¹ûÊÇ8Ôò¿ÉÒÔÅÐ¶¨ÊÇµÇÈë¼ÇÂ¼ °Ñ¼ÇÂ¼Ð´ÈëµÇ³ölist
            {
                pair<string,long> item = make_pair(logrec.getString(),logrec.logtime);
                m_logouts.insert(item);
                logout_num++;
            }
        }
    }
    fin.close();  //¹Ø±ÕÎÄ¼þÁ÷
    cout<<"loginFile size:"<<m_logins.size()<<endl;
    cout<<"logoutFile size:"<< m_logouts.size()<<endl;
    cout<<"end read backupFile!"<<endl<<endl;
}
//»ñÈ¡±¸·ÝÎÄ¼þÃû ¹¹Ôìº¯ÊýÖÐµ÷ÓÃ³õÊ¼»¯m_logFile±äÁ¿
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

void LogReader::readLoginsFile() throw(ReadException) //¶ÁÈ¡ÉÏ´ÎÎ´Æ¥Åä³É¹¦µÄÐÅÏ¢ÎÄ¼þ
{
    fstream fin;
    fin.open(m_loginsFile.c_str(),ios::binary|ios::in); //ÒÔ¶þ½øÖÆÐ´µÄ·½Ê½´ò¿ªm_loginsFileÎÄ¼þ
    if(!fin.is_open())
    {
        cerr<<"Read LoginsFile error!"<<endl;
    }
    fin.seekg(0,ios::end);
    int fsize = fin.tellg()/372;
    
    fin.seekg(0,ios::beg);
    cout<<"Start read last time unsuccessful match data!"<<endl;
    for(int i=0; i<fsize; i++)
    {
        LogRec logrec;
        int  pos=i*372;    //ÎÄ¼þÖÐÃ¿Ìõ¼ÇÂ¼µÄ¿ªÊ¼Î»ÖÃ
        fin.seekg(pos,ios::beg);//½«ÎÄ¼þÖ¸ÕëÖ¸ÏòÒ»Ìõ¼ÇÂ¼µÄ¿ªÊ¼Î»ÖÃ
        fin.read((char*)&(logrec.logname),sizeof(logrec.logname));//¶ÁÈ¡¼ÇÂ¼ÖÐµÇÂ¼Ãû
        fin.seekg(pos+68,ios::beg); //½«ÎÄ¼þÖ¸ÕëÌø¹ý68×Ö½Ú£¬Ö¸ÏòµÇÂ¼idµÄÐÅÏ¢Î»ÖÃ
        fin.read((char*)&(logrec.pid),sizeof(logrec.pid));//¶ÁÈ¡id
        fin.seekg(80+pos,ios::beg);//Ô­ÀíÍ¬ÉÏ
        fin.read((char*)&(logrec.logtime),sizeof(logrec.logtime));
        fin.seekg(114+pos,ios::beg);
        fin.read((char*)&(logrec.logip),sizeof(logrec.logip));
        m_logins.push_back(logrec);                   //½«¶ÁÈ¡µÄÎ´Æ¥Åä¼ÇÂ¼²åÈëµÇÈë¼ÇÂ¼list
    }
    fin.close();
    cout<<"total: "<<fsize<<" unmatched data!"<<endl;
    cout<<"total login data: "<<m_logins.size()<<endl;
    cout<<"Read unmatched match data over!"<<endl<<endl;
}

void LogReader::match() throw(SocketException)              //Æ¥ÅäµÇÈëµÇ³öÊý¾Ý
{
    cout<<"Start match login data with logout data!"<<endl;
    /*
    list<LogRec>::iterator init;   //Ö¸Ïò¼ÇÂ¼µÇÈëÐÅÏ¢listµÄµü´úÆ÷
    list<LogRec>::iterator outit;  //Ö¸Ïò¼ÇÂ¼µÇÈëÐÅÏ¢listµÄµü´úÆ÷
    for(outit=m_logouts.begin(); outit!=m_logouts.end(); outit++)  //Ë«ÖØÑ­»· ÓÃµÇÈë¼ÇÂ¼ºÍµÇ³ö¼ÇÂ¼ÖðÌõ±È¶Ô
    {
        for(init=m_logins.begin(); init!=m_logins.end(); init++)
        {
            if(*init == *outit) //ifÌõ¼þ³ÉÁ¢ÔòÆ¥Åä³É¹¦ °ÑÊý¾ÝÐ´ÈëÆ¥Åä³É¹¦list ÇÐ¼ÇµÇÈëÊ±¼ä±Ø¶¨Ð¡ÓÚµÇ³öÊ±¼ä
            {
                MLogRec mlogrec;
                strcpy(mlogrec.logname,outit->logname);
                strcpy(mlogrec.logip,outit->logip);
                mlogrec.pid=outit->pid;
                mlogrec.logintime=init->logtime;
                mlogrec.logouttime=outit->logtime;
                mlogrec.logtime=outit->logtime-init->logtime;
                m_logs.push_back(mlogrec);
                init=m_logins.erase(init);         //½«Æ¥ÅäÍê³ÉµÄµÇÈë¼ÇÂ¼´Óm_loginsµÇÈë¼ÇÂ¼±íÖÐÉ¾³ý
                break;
            }
        }
        outit=m_logouts.erase(outit);             //½«Æ¥ÅäÍê³ÉµÄµÇ³ö¼ÇÂ¼´Óm_logoutsµÇ³ö¼ÇÂ¼±íÖÐÉ¾³ý
    }
    */
    list<LogRec>::iterator init = m_logins.begin();
    while(init != m_logins.end())
    {
        string init_str = init->getString();
        multimap<string,long>::iterator find_it = m_logouts.find(init_str);
        if(find_it != m_logouts.end())
        {
            MLogRec mlogrec;
            strcpy(mlogrec.logname,init->logname);
            strcpy(mlogrec.logip,init->logip);
            mlogrec.pid = init->pid;
            mlogrec.logintime = init->logtime;
            mlogrec.logouttime = find_it->second;
            mlogrec.logtime = find_it->second - init->logtime;
            m_logs.push_back(mlogrec);    
            m_logouts.erase(find_it);
            init = m_logins.erase(init);
        }
        else
        {
            ++init;
        }
    }
    m_logouts.clear();//清空map
    cout<<"total matched:"<<m_logs.size()<<endl;
    cout<<"Match login with logout over!"<<endl<<endl;
}

void LogReader::saveLoginsFile() throw(SaveException)       //½«Î´Æ¥Åä³É¹¦µÄ¼ÇÂ¼±£´æ
{
    fstream fout;
    fout.open(m_loginsFile.c_str(),ios::binary|ios::out|ios::app);
    if(!fout.is_open())
    {
        throw SaveException("Open last time unmatched data faile!");
    }
    int count = m_logins.size();
    int logrec_size=sizeof(LogRec);
    list<LogRec>::iterator init;
    for(init=m_logins.begin(); init!=m_logins.end(); init++)
    {
        fout.write((char*)(&(*init)),logrec_size);
    }
    fout.close();
    cout<<"Over!"<<endl;
    cout<<"total:"<<count<<endl;
}

LogReader::~LogReader()
{

}
