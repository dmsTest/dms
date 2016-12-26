#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "data.h"
#include "log_dao.h"
#include "server.h"
using namespace std;

short _port = 8888;
string _ip = "127.0.0.1";

int main(int argc, char **argv)
{
   // FileDao dao("./data.dat");
    MysqlDao sqlDao("root","123456");
    Server server(sqlDao, _port, _ip);
    server.dataMine();
    return 0;
}
