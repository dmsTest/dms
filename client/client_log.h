#ifndef  __LOG_H_
#define __LOG_H_

#include <iostream>
#include "singleton.h"

#define MAX_LINE   4096

using namespace std;

enum E_LOG_TYPE
{
	E_LOG_NORMAL = 0,
	E_LOG_ERROR,
	E_LOG_END
};

// class function:write log to logfile.txt
// use as: Singleton<Log>::getInstance()->write_log(E_LOG_NORMAL,"%s\n","test log");
class Log : public Noncopyable
{
public:
	Log(string normal_filename = "log_normal.txt",string error_filename = "log_error.txt");
	~Log();
	void write_log(E_LOG_TYPE log_type,const char *fmt,...);
private:
	string m_normal_filename;
	string m_error_filename;
	int m_normal_fd;
	int m_error_fd;
};

#endif