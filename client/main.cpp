#include <iostream>
#include "Client.h"
#include "ClientException.h"
#include "LogReader.h"
#include "LogSender.h"
#include <string>
#include <cstring>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

std::string _ip = "127.0.0.1";
short _port = 8888;

std::string getWtmpxString()
{
	time_t now_time;
	time(&now_time);
	struct tm *now_tm;
	now_tm = localtime(&now_time);
	char wtmpxFile[20];
	sprintf(wtmpxFile,"wtmpx.%04d%02d%02d%02d%02d%02d",now_tm->tm_year+1900,now_tm->tm_mon+1,now_tm->tm_mday,now_tm->tm_hour,now_tm->tm_min,now_tm->tm_sec);
	std::string str(wtmpxFile);
	std::cout << str << std::endl;
	return str;
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		try{
			std::string logFile = getWtmpxString();
			std::string loginsFile = "logins.dat";
			LogReader reader(logFile,loginsFile);
			ConsoleSender consoleSender;
			//SocketSender socketSender("./fail.dat",_port,_ip);
			//Client client(reader,socketSender);
			Client client(reader,consoleSender);
			client.dataMine();
		} catch(ClientException& ex)
		{
			cout << ex.what() << endl;
			return -1;
		}
	}
	else
	{
		if(!strcmp(argv[1],"-g"))
		{
			cout << "start the gui..." << endl;
			return -1;
		}
		else
		{
			cout << "format is error,eg: ./main -g" << endl;
			return 0;
		}
	}
	return 0;
}

