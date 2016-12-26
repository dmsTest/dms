#include "log_sender.h"
#include <unistd.h>
#include "tcp_client.h"
#include "client_log.h"
#include <string.h>
#include <time.h>

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

SocketSender::SocketSender(const std::string &failFile)
	:m_failFile(failFile)
{

}

void SocketSender::sendLog(std::list<MLogRec> &logs) throw(SendException)
{
	readFailFile(logs);
	std::list<MLogRec>::iterator it = logs.begin();
	while(it != logs.end())
	{
		MLogRec send_data = *it;
		bool isSend = sendData(send_data);
		if(isSend)
			it = logs.erase(it);
		else
			break;
	}
	saveFailFile(logs);
}


bool SocketSender::connectServer()
{
	int state = Singleton<Tcp_client>::getInstance()->connect_server();
	if( state == 0 )
	{
		Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","----------connect server success-----------");
		std::cout << "connect server success" << std::endl;
		return true;
	}
	else
	{
		Singleton<Log>::getInstance()->write_log(E_LOG_ERROR,"%s\n","----------connect server fail-----------");
		std::cout << "connect server fail" << std::endl;
		return false;
	}
}

void SocketSender::readFailFile(std::list<MLogRec>& logs) throw(ReadException)
{
	//m_logFile,if sock connect success,read fail file
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

bool SocketSender::sendData(MLogRec &send_data) throw(SendException)
{
	NET_C2S_match_data send;
	strncpy(send.log_data.username,send_data.username,sizeof(send.log_data.username));
	strncpy(send.log_data.logname,send_data.logname,sizeof(send.log_data.logname));
	strncpy(send.log_data.logip,send_data.logip,sizeof(send.log_data.logip));
	send.log_data.pid = send_data.pid;
	send.log_data.logintime = send_data.logintime;
	send.log_data.logouttime = send_data.logouttime;
	send.log_data.logtime = send_data.logtime;
	TCP_CLIENT_SEND(&send,send.msg_size);
	return true;
}

void SocketSender::saveFailFile(std::list<MLogRec>& logs) throw(SaveException)
{
	std::ofstream ofs(m_failFile.c_str());
	for(std::list<MLogRec>::iterator it = logs.begin(); it != logs.end(); ++it)
	{
		ofs << it->logname << " " << it->logip << " " << it->pid <<  " "
				<< it->logintime << " " << it->logouttime << " "
					<< it->logtime << std::endl;
	}
}

bool SocketSender::is_register()
{
	int pre_time = time(NULL);
	while(1)
	{
		// if overtime,break,then return false
		int cur_time = time(NULL);
		if( cur_time - pre_time > WAIT_SEC)
			break;
		bool is_success = Singleton<Tcp_client>::getInstance()->is_register();
		if( is_success )
			return true;
	}
	return false;
}
        
bool SocketSender::is_login()
{
	int pre_time = time(NULL);
	while(1)
	{
		// if overtime,break,then return false
		int cur_time = time(NULL);
		if( cur_time - pre_time > WAIT_SEC)
			break;
		bool is_success = Singleton<Tcp_client>::getInstance()->is_login();
		if( is_success )
			return true;
	}
	return false;
}

SocketSender::~SocketSender()
{
	
}
