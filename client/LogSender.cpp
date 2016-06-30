#include "LogSender.h"
#include <unistd.h>

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
	:LogSender(),m_failFile(failFile),m_port(port),m_ip(ip)
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
    serv_addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    serv_addr.sin_port = htons(m_port);
    connect(m_sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
}

void SocketSender::readFailFile(std::list<MLogRec>& logs) throw(ReadException)
{
	//m_logFile,if sock connect success,read fail file
    if(!m_sockfd)
	{
		std::ifstream ifs(m_failFile.c_str());
		std::string line;
		while(std::getline(ifs,line))
		{
            MLogRec item = {};
            std::istringstream iss(line);
            iss >> item.logname;
            iss >> item.logip;
            iss >> item.pid;
            iss >> item.logintime;
            iss >> item.logouttime;
            iss >> item.logtime;
         	logs.push_back(item);
		}
	}
}

void SocketSender::sendData(std::list<MLogRec>& logs) throw(SendException)
{
	for(std::list<MLogRec>::iterator it = logs.begin(); it != logs.end(); ++it)
	{
		ssize_t retval = write(m_sockfd,(char*)(&(*it)),sizeof(MLogRec));
		if(retval != 0)
		{
			std::cout << "socket error, send error!" << std::endl;
			close(m_sockfd);
			return; 
		}
		/*
		write(m_sockfd,it->logname,sizeof(it->logname));
		write(m_sockfd,it->logip,sizeof(it->logip));

		std::string s_pid = converTToString<pid_t>(it->pid);
		std::string s_logintime = converTToString<long>(it->logintime);
		std::string s_logouttime = converTToString<long>(it->logouttime);
		std::string s_logtime = converTToString<long>(it->logtime);

		write(m_sockfd,s_pid.c_str(),s_pid.size());
		write(m_sockfd,s_logintime.c_str(),s_logintime.size());
		write(m_sockfd,s_logouttime.c_str(),s_logouttime.size());
		write(m_sockfd,s_logtime.c_str(),s_logtime.size());
		*/
	}

}

void SocketSender::saveFailFile(std::list<MLogRec>& logs) throw(SaveException)
{
	//
	if(m_sockfd == -1)
	{
		std::ofstream ofs(m_failFile.c_str());
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
