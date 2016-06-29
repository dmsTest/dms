#include <iostream>
#include "Client.h"
#include "ClientException.h"
#include "LogReader.h"
#include "LogSender.h"
#include <string>

using namespace std;

std::string m_ip = "127.0.0.1";
short m_port = 8888;

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		try{
			LogReader reader("./wtmpx","./logins.dat");
			ConsoleSender consoleSender;
			//SocketSender socketSender("./fail.dat",m_port,m_ip);
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

