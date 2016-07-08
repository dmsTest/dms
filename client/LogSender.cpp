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
			", logintime: " << it->logintime <<
			", logouttime: " << it->logouttime <<
			", logtime: " << it->logtime << std::endl;
	}
	logs.clear();
	std::cout << "log size: " << logs.size() << std::endl;
}

SocketSender::SocketSender(const std::string &failFile, short port,const std::string &ip)
	:LogSender(),m_failFile(failFile),m_port(port),m_ip(ip),is_closed(false)
{

}

void SocketSender::sendLog(std::list<MLogRec> &logs) throw(SendException)
{
	readFailFile(logs);
//	sendData(logs);
	std::list<MLogRec>::iterator it = logs.begin();
	while(it != logs.end())
	{
		Msg msg;
		msg.type = DATA;
		msg.data.logdata = *it;	
		bool isSend = sendData(msg);
		if(isSend)
			it = logs.erase(it);
		else
			break;
	}
	saveFailFile(logs);
}


void SocketSender::connectServer()
{
	m_sockfd = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    serv_addr.sin_port = htons(m_port);
    int fd = connect(m_sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(fd != -1)
    {
	    std::cout << "connect success!" << std::endl;
    }
    else
    {
	    std::cout << "connect fail!" << std::endl;
    }
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

bool SocketSender::recvData() throw(SendException)
{
	//recv from server("yes" or "no")
	while(1)
	{
		char buf[5];
		int rel = recv(m_sockfd,buf,sizeof(buf),0);
		std::cout << buf << std::endl;
		if(rel != 0)
		{
			if(strcmp(buf,"yes")==0)
				return true;
			else
				return false;
		}
	}
	return false;
}

bool SocketSender::sendData(Msg &msg) throw(SendException)
{
	//need update
	ssize_t retval = send(m_sockfd,(char*)(&(msg)),sizeof(Msg),0);
	if(retval == -1)
	{
		std::cout << "socket error, send error!" << std::endl;
		close(m_sockfd);
		is_closed = true;
		return false; 
	}
		/*
		std::cout << "logname: " << it->logname << ", logip: " << it->logip
		       << ", pid: " << 	it->pid << ", logintime: " << it->logintime
		       		<< ", logouttime: " << it->logouttime << "logtime: " << it->logtime << std::endl;
		*/
	
	return true;
}

void SocketSender::saveFailFile(std::list<MLogRec>& logs) throw(SaveException)
{
	//
	std::ofstream ofs(m_failFile.c_str());
	for(std::list<MLogRec>::iterator it = logs.begin(); it != logs.end(); ++it)
	{
		ofs << it->logname << " " << it->logip << " " << it->pid <<  " "
				<< it->logintime << " " << it->logouttime << " "
					<< it->logtime << std::endl;
	}
}

SocketSender::~SocketSender()
{
	if(!is_closed)
	{
		close(m_sockfd);	
	}
}
