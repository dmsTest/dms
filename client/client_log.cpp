#include "client_log.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdarg.h>

using namespace std;

Log::Log(string normal_filename,string error_filename):
	m_normal_filename(normal_filename),
	m_error_filename(error_filename)
{
	m_normal_fd = open(m_normal_filename.c_str(),O_WRONLY | O_CREAT);
	m_error_fd = open(m_error_filename.c_str(),O_WRONLY | O_CREAT);
	if( m_normal_fd < 0 || m_error_fd < 0)
	{
		cerr << "open or create log file error" << endl;
		exit(EXIT_FAILURE);
	}
}

Log::~Log()
{
	close(m_normal_fd);
	close(m_error_fd);
}

void Log::write_log(E_LOG_TYPE log_type,const char *fmt,...)
{
	char buf_line[MAX_LINE];
	va_list pArgs;
	va_start(pArgs,fmt);
	vsnprintf(buf_line,sizeof(buf_line),fmt,pArgs);
	va_end(pArgs);
	switch(log_type)
	{
	case E_LOG_NORMAL:
		write(m_normal_fd,buf_line,sizeof(buf_line));
		break;
	case E_LOG_ERROR:
		write(m_error_fd,buf_line,sizeof(buf_line));
		break;
	default:
		break;
	}
}