//数据对象类型定义
#ifndef _DATA_H
#define _DATA_H
#include <unistd.h>//pid_t等uc数据类型和函数
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>

//type to string
template<typename T>
std::string converTToString(const T &value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();	
}

//string to type
template<typename T>
T converStringToT(const std::string &str)
{
	std::stringstream ss;
	ss << str;
	return ss.str();
}

//匹配日志记录
struct MLogRec
{
    char logname[32];
    char logip[32];
    pid_t pid;
    long logintime;
    long logouttime;
    long logtime;

    bool operator!=(const MLogRec &right)
    {
        return !(*this == right);
    }

    bool operator==(const MLogRec &right)
    {
        if( strcmp(logname,right.logname)==0 &&
                strcmp(logip,right.logip)==0 &&  pid==right.pid && logtime>=0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }


};


#endif

