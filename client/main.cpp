#include <iostream>
#include "Client.h"
#include "ClientException.h"
#include "data.h"
#include "LogReader.h"
#include "LogSender.h"
#include <string>

using namespace std;

std::string m_ip = "127.0.0.1";
int m_port = 8888;

int main(int argc, char** argv)
{
	std::string logFile = "wtmpx";
	std::string loginFile = "";
	std::string failFile = "";
	LogReader reader(logFile,loginFile);
	SocketSender socketSender(failFile,m_port,m_ip);
	Client client(reader,socketSender);
	
	client.dataMine();

	return 0;
}

