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

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		try{
			std::string logFile = "wtmpx";
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

