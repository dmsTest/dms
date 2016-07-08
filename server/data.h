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

enum MsgType { REG=0,LOGIN,DATA  };
//register msg
struct MRegister
{
    char username[32];
    char password[32];
    char gender[4];
    char phone[12];
};

//login msg
struct MLogin
{
    char username[32];
    char password[32];
};

//匹配日志记录
struct MLogRec
{
    char username[32];	
    char logname[32];
    char logip[32];
    pid_t pid;
    long logintime;
    long logouttime;
    long logtime;

    /*
    MLogRec& operator=(const MLogRec &right)
    {
        strcpy(logname,right.logname);
        strcpy(logip,right.logip);
	pid = right.pid;
        logintime = right.logintime;
        logouttime = right.logouttime;
        logtime = right.logtime;
	return *this;
    }

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
    */

};

struct Msg
{
       enum MsgType type;
       union
       {
         struct MRegister reg;
	 struct MLogin login;
	 struct MLogRec logdata;	 
       } data;
};

#endif

