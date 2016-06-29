#include "LogSender.h"

LogSender::LogSender()
{
    //ctor
}

LogSender::~LogSender()
{
    //dtor
}

void ConsoleSender::sendLog(std::list<MLogRec> &logs)throw(SendException)
{
	//write to order_line,then write to the gui list
	for(std::list<MLogRec>::iterator it = logs.begin(); it != logs.end(); ++it)
	{
		std::cout << "logname: " << it->logname << 
			", logip: " << it->logip << 
			", pid: " << it->pid <<  
			", logintime " << it->logintime <<
			", logouttime: " << it->logouttime <<
			", logtime: " << it->logtime << std::endl;
	}
}

SocketSender::SocketSender(const std::string &failFile, short port,const std::string &ip)
	:m_failFile(failFile),m_port(port),m_ip(ip)
{
	
}

void SocketSender::sendLog(std::list<MLogRec> &logs) throw(SendException)
{
	readFailFile(logs);
	connectServer();
	sendData(logs);
	saveFailFile(logs);
}

std::string m_failFile;
        short m_port;
        std::string m_ip;
        int m_sockfd;

void SocketSender::connectServer()
{
	m_sockfd = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_ip);
    serv_addr.sin_port = htons(m_port);
    connect(m_sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
}

void SocketSender::readFailFile(std::list<MLogRec>& logs) throw(ReadException)
{
	//m_logFile,if sock connect success,read fail file 
    if(!m_sockfd)
	{
		std::ofstream ofs(m_failFile);
		std::string line;
		while(std::getline(ofs,line))
		{
            MLogRec item();
            std::ostringstream oss(line);
            oss >> item.logname;
            oss >> item.logip;
            oss >> item.pid;
            oss >> item.logintime;
            oss >> item.logouttime;
            oss >> item.logtime;
         	logs.push_back(item);   
		}
	}
}

void SocketSender::sendData(std::list<MLogRec>& logs) throw(SendException)
{
	for(std::list<MLogRec>::iterator it = logs.begin(); it != logs.end(); ++it)
	{
		write(m_sockfd,it->logname,sizeof(it->logname));
		write(m_sockfd,it->logip,sizeof(it->logip));

		std::string s_pid = converTToString<pid>(it->pid);
		std::string s_logintime = converTToString<long>(it->logintime);
		std::string s_logouttime = converTToString<long>(it->logouttime);
		std::string s_logtime = converTToString<long>(it->logtime);
		
		write(m_sockfd,s_pid,s_pid.size());
		write(m_sockfd,s_logintime,s_logintime.size());
		write(m_sockfd,s_logouttime,s_logouttime.size());
		write(m_sockfd,s_logtime,s_logtime.size());
	}

}
     
void SocketSender::saveFailFile(std::list<MLogRec>& logs) throw(SaveException)
{
	//
	if(sock == -1)
	{
		std::ofstream ofs(m_failFile);
		for(std::list<MLogRec>::iterator it = logs.begin(); it != logs.end(); ++it)
		{
			ofs << it->logname << " " << it->logip << " " << it->pid <<  " " 
					<< it->logintime << " " << it->logouttime << " " 
						<< it->logtime << std::endl;
		} 
	}
}

SocketSender::~SocketSender()
{
	close(m_sockfd);
}