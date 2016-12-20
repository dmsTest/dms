#include <iostream>
#include <string>
#include <cstring>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include "Client.h"
#include "ClientException.h"
#include "LogReader.h"
#include "LogSender.h"
#include "Log.h"
#include "data.h"

using namespace std;

extern std::string _ip;
extern short _port;
extern SocketSender socketSender;
extern std::string g_username;

bool registerFunc(Msg &msg)
{
	std::string username,gender,phone;
	char *password,*repassword;
	std::cout << "please input the name(length<32): ";
	std::cin >> username;
	if(username.size() >= 32)
	{
		std::cout << "length is too longer!!!" << std::endl;
		std::cout << "register fail!!!" << std::endl;
		return false;	
	}
       	password=getpass("please input the password(6<length<32):");    /*输入密码*/
 	std::string p_str(password);	
	if(p_str.size() >= 32 || p_str.size() <= 6)
	{
		std::cout << "length is too longer or too shorter!!!" << std::endl;
		std::cout << "register fail!!!" << std::endl;
		return false;
	}
	
	repassword=getpass("please repeat input the password: ");
	std::string rp_str(repassword);
	if(p_str != rp_str)
	{
		std::cout << "password is not match!!!" << std::endl;
		std::cout << "register fail!!!" << std::endl;
		return false;
	}
	std::cout << "please input gender(man or woman): ";
	std::cin >> gender;
	if(strcmp(gender.c_str(),"man")!=0 && strcmp(gender.c_str(),"woman")!=0)
	{
		std::cout << "gender is error!!!" << std::endl;
		std::cout << "register fail!!!" << std::endl;
		return false;
	}
	std::cout << "please input the phone(length=11): ";
	std::cin >> phone;
	if(phone.size()!=11)
	{
		std::cout << "length is not match!!!" <<std::endl;
		std::cout << "register fail!!!" << std::endl;
		return false;
	}
	strcpy(msg.data.reg.username,username.c_str());
	strcpy(msg.data.reg.password,p_str.c_str());
	if(gender == "man")
	{
		strcpy(msg.data.reg.gender,"男");
	}
	else
	{
		strcpy(msg.data.reg.gender,"女");
	}
	strcpy(msg.data.reg.phone,phone.c_str());
	bool isSend = socketSender.sendData(msg);
	if(!isSend)
	{
		std::cout << "connect server fail!!!" << std::endl;
		return false;
	}
	g_username = username;
	return true;
}

bool loginFunc(Msg &msg)
{
	std::string username;
	std::cout << "please input the name(length<32): ";
	std::cin >> username;
	if(username.size() >= 32)
	{
		std::cout << "length is too longer!!!" << std::endl;
		std::cout << "login fail!!!" << std::endl;
		return false;
	}
	char *p;
	p=getpass("please input the password(6<length<32): ");
	std::string password(p);
	if(password.size()<=6 || password.size()>=32)
	{
		std::cout << "length is too longer or too shorter!!!" <<std::endl;
		std::cout << "login fail!!!" << std::endl;
		return false;
	}
	strcpy(msg.data.login.username,username.c_str());
	strcpy(msg.data.login.password,password.c_str());
	bool isSend = socketSender.sendData(msg);
 	//std::cout << isSend << std::endl; 
	if(!isSend)
		return false;
	g_username = username;
	return true;
}

int main(int argc, char** argv)
{
	socketSender.connectServer();
	Msg msg;
	bool success = false;
	if(argc > 1)
	{
		while(true)
		{
			if(strcmp(argv[1],"-r")==0)
			{
				//register
				msg.type = REG;
				bool isSuccess = registerFunc(msg);
				if(isSuccess)
				{
					//recv from server("yes" or "no")
					bool isOk = socketSender.recvData();
					if(isOk)
					{
						//register ok
						std::cout << "register ok"<<std::endl;
						usleep(1000000);
						success = true;
					}
					else
					{
						std::cout << "register fail!!!" << std::endl;
					}
					break;
				}
				else
				{
					//end this client
					return -1;
				}
			}	
			else if(strcmp(argv[1],"-l")==0)
			{
				//login
				//read username and then read passwd
				msg.type = LOGIN;
				bool isSuccess = loginFunc(msg);
				if(isSuccess)
				{
					//recv from server("yes" or "no")
					bool isOk = socketSender.recvData();
					if(isOk)
					{
						//login ok
						std::cout << "login ok" << std::endl;
						usleep(1000000);
						success = true;
					}
					else
					{
						std::cout << "name or password is error!!!" << std::endl;
					}
					break;
				}	
				else
				{
					return -1;
				}		
			}
			else
			{
				std::cout << "format is error!!!(eg: ./client -r/-l/-g)" << std::endl;
				return -1;
			}
			
		}
	}
	else
	{
		//start gui(default)
	}
	std::cout << success << std::endl;
	std::cout << g_username << std::endl;
	if(success)
	{
		try{
			std::string logFile = "wtmpx";
			std::string loginsFile = "logins.dat";
			LogReader reader(logFile,loginsFile);
			//ConsoleSender consoleSender;
			Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","---------socket sender-----");
			Client client(reader,socketSender);
			//Client client(reader,consoleSender);
			client.dataMine();
		} catch(ClientException& ex)
		{
			cout << ex.what() << endl;
			return -1;
		}
	}
	return 0;
}

