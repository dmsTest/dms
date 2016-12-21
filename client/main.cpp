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
#include "Net_base.h"
#include "Tcp_client.h"

using namespace std;

extern SocketSender socketSender;
extern std::string g_username;

bool registerFunc()
{
	NET_C2S_register send;
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
	strcpy(send.user_name,username.c_str());
	strcpy(send.user_password,p_str.c_str());
	if(gender == "man")
	{
		strcpy(send.gender,"男");
	}
	else
	{
		strcpy(send.gender,"女");
	}
	strcpy(send.phone,phone.c_str());
	TCP_CLIENT_SEND(&send,send.msg_size);
	g_username = username;
	return true;
}

bool loginFunc()
{
	NET_C2S_login send;
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
	strcpy(send.user_name,username.c_str());
	strcpy(send.user_password,password.c_str());
	
	TCP_CLIENT_SEND(&send,send.msg_size);
 	g_username = username;
	return true;
}

bool start(int argc,char **argv)
{
	bool success = false;
	if(argc > 1)
	{
		while(true)
		{
			if(strcmp(argv[1],"-r")==0)
			{
				//register
				bool isSuccess = registerFunc();
				if(isSuccess)
				{
					//recv from server("yes" or "no")
					bool isOk = socketSender.is_register();
					if(isOk)
					{
						//register ok
						std::cout << "register ok"<<std::endl;
						sleep(1);
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
					return false;
				}
			}	
			else if(strcmp(argv[1],"-l")==0)
			{
				//login
				//read username and then read passwd
				bool isSuccess = loginFunc();
				if(isSuccess)
				{
					//recv from server("yes" or "no")
					bool isOk = socketSender.is_login();
					if(isOk)
					{
						//login ok
						std::cout << "login ok" << std::endl;
						sleep(1);
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
					return false;
				}		
			}
			else
			{
				std::cout << "format is error!!!(eg: ./client -r/-l/-g)" << std::endl;
				return false;
			}
			
		}
	}
	return success;
}

int main(int argc, char** argv)
{
	bool is_connect = socketSender.connectServer();
	if( !is_connect )
		exit(EXIT_FAILURE);

	bool success = start(argc,argv);
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

