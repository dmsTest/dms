#include "data.h"
#include "LogSender.h"

std::string g_username="";
std::string _ip = "127.0.0.1";
short _port = 8888;
SocketSender socketSender("./fail.dat",_port,_ip);

