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

list<MLogRec>&  LogReader::readLog()  //��ȡ��¼��־�ļ�������ȡ��Ϣ������list��
{
    backup();         //���ñ��ݺ��������ļ�����
    readLoginsFile(); //��ȡ�ϴ�δƥ���¼�ļ�
    readBackupFile(); //��ȡ��־��¼�ı����ļ�
    match();          //��ʼ����ǳ���¼ƥ��
    saveLoginsFile(); //��δƥ��ļ�¼�������ļ���
    return m_logs;
}

void LogReader::backup() throw(BackupException)
{
    string str="./backup "+backup;
    system(str.c_str);//����Linux�µ�shell�ű��ļ� ������־��¼wtmpx�ļ�����
}

void LogReader::readBackupFile() throw(BackupException)   //��ȡ���ݵ���־�ļ�
{
    unsigned type=0;//�����ж��ǵ��뻹�ǵǳ�
    fstream fin;
    fin.open(m_backupFile.c_str(),ios::binary|ios::in);
    if(!fin.is_open())
    {
        cout<<"open file faile!"<<endl;

    }
    fin.seekg(0,ios::end);
    int fsize = fin.tellg()/372;  //������ݵ���־�ļ��еĵ���ǳ���¼��Ŀ
    fin.seekg(0,ios::beg);
    cout<<"start read backupFile!"<<endl;
    for(int i=0; i<fsize; i++)
    {
        int login_num,logout_num;
        login_num=logout_num=0;
        LogRec logrec;
        int  pos=i*372;         //�趨�ļ�ָ��ÿ�ζ�ȡ��¼ʱ��λ�ã�ÿ�ζ�ȡ����һ����¼�Ŀ�ʼ��
        fin.seekg(pos,ios::beg);
        fin.read((char*)&(logrec.logname),sizeof(logrec.logname));  //��ȡ��¼��¼�ĵ�¼��
        if(logrec.logname[0]!='.')//�ж��Ƿ�Ϊ�շ��û��ļ�¼
        {
            fin.seekg(pos+68,ios::beg);  //���ļ�ָ��ָ���n����¼�ĵ�¼idλ��
            fin.read((char*)&(logrec.pid),sizeof(logrec.pid));//��ȡ��¼id
            logrec.pid=htonl(logrec.pid);//��������������ת����������
            fin.seekg(72+pos,ios::beg);  //ԭ��ͬ��
            fin.read((char*)&type,sizeof(type));
            type = htons(type);
            fin.seekg(80+pos,ios::beg);
            fin.read((char*)&(logrec.logtime),sizeof(logrec.logtime));
            logrec.logtime = htonl(logrec.logtime);
            fin.seekg(114+pos,ios::beg);
            fin.read((char*)&(logrec.logip),sizeof(logrec.logip));
            if(type==7)          //�����7������ж��ǵ����¼ �Ѽ�¼д�����list
            {
                m_logins.push_back(logrec);
                lonin_num++;

            }
            else if(type==8)    //�����8������ж��ǵ����¼ �Ѽ�¼д��ǳ�list
            {
                m_logouts.push_back(logrec);
                logout_num++;
            }
        }
    }
    fin.close();  //�ر��ļ���
    cout<<"end read backupFile!"<<endl;
}
//��ȡ�����ļ��� ���캯���е��ó�ʼ��m_logFile����
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

void LogReader::readLoginsFile() throw(ReadException) //��ȡ�ϴ�δƥ��ɹ�����Ϣ�ļ�
{
    fstream fin;
    fin.open(m_loginsFile.c_str(),ios::binary|ios::in); //�Զ�����д�ķ�ʽ��m_loginsFile�ļ�
    if(!fin.is_open())
    {
        cerr<<"Read LoginsFile error!"<<endl;
    }
    fin.seekg(0,ios::end);
    int fsize = fin.tellg()/372;
    cout<<"����"<<fsize<<"��δƥ���¼��"<<endl;
    fin.seekg(0,ios::beg);
    cout<<"start read unsuccessful match data!"<<endl;
    for(int i=0; i<fsize; i++)
    {
        LogRec logrec;
        int  pos=i*372;    //�ļ���ÿ����¼�Ŀ�ʼλ��
        fin.seekg(pos,ios::beg);//���ļ�ָ��ָ��һ����¼�Ŀ�ʼλ��
        fin.read((char*)&(logrec.logname),sizeof(logrec.logname));//��ȡ��¼�е�¼��
        fin.seekg(pos+68,ios::beg); //���ļ�ָ������68�ֽڣ�ָ���¼id����Ϣλ��
        fin.read((char*)&(logrec.pid),sizeof(logrec.pid));//��ȡid
        fin.seekg(80+pos,ios::beg);//ԭ��ͬ��
        fin.read((char*)&(logrec.logtime),sizeof(logrec.logtime));
        fin.seekg(114+pos,ios::beg);
        fin.read((char*)&(logrec.logip),sizeof(logrec.logip));
        m_logins.push_back(logrec);                   //����ȡ��δƥ���¼��������¼list
    }
    fin.close();
    cout<<"end read unsuccessful match data!"<<endl;
}

void LogReader::match() throw(SocketException)              //ƥ�����ǳ�����
{
    cout<<"start match login and logout data!"<<endl;
    list<LogRec>::iterator init;   //ָ���¼������Ϣlist�ĵ�����
    list<LogRec>::iterator outit;  //ָ���¼������Ϣlist�ĵ�����
    for(outit=m_logouts.begin(); outit!=m_logouts.end(); outit++)  //˫��ѭ�� �õ����¼�͵ǳ���¼�����ȶ�
    {
        for(init=m_logins.begin(); init!=m_logins.end(); init++)
        {
            if(strcmp(outit->logname,init->logname)==0
                    &&strcmp(outit->logip,init->logip)==0&&
                    outit->pid==init->pid&&outit->logtime>init->logtime) //if����������ƥ��ɹ� ������д��ƥ��ɹ�list �мǵ���ʱ��ض�С�ڵǳ�ʱ��
            {
                MLogRec mlogrec;
                strcpy(mlogrec.logname,outit->logname);
                strcpy(mlogrec.logip,outit->logip);
                mlogrec.pid=outit->pid;
                mlogrec.logintime=init->logtime;
                mlogrec.logouttime=outit->logtime;
                mlogrec.logtime=outit->logtime-init->logtime;
                m_logs.push_back(mlogrec);
                init=m_logins.erase(init);         //��ƥ����ɵĵ����¼��m_logins�����¼����ɾ��
            }
        }
        outit=m_logouts.erase(outit);             //��ƥ����ɵĵǳ���¼��m_logouts�ǳ���¼����ɾ��
    }
    cout<<"mogin and logout data over!"<<endl;
}

void LogReader::saveLoginsFile() throw(SaveException)       //��δƥ��ɹ��ļ�¼����
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
