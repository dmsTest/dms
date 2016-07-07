//数据对象类型定义
#ifndef _DATA_H
#define _DATA_H
#include <unistd.h>//pid_t等uc数据类型和函数
#include <cstring>
#include <sstream>

//test ljm
//登入登出日志记录
struct LogRec
{
   char logname[32];     //登入名
   char logip[32];       //登入ip
   pid_t pid;            //登入进程号
   long logtime;         //登入或登出时间

   bool operator!=(const LogRec &right)
   {
      return !(*this==right);
   }

   bool operator==(const LogRec &right)
   {
      if(strcmp(logname,right.logname) == 0 &&
         strcmp(logip,right.logip) == 0 && pid == right.pid)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   std::string getString()
   {
     std::stringstream ss;
     ss << logname << logip << pid;
     return ss.str(); 
   }
};

enum MsgType { REG=0,LOGIN,DATA };

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
   char logname[32];
   char logip[32];
   pid_t pid;
   long logintime;
   long logouttime;
   long logtime;
   MLogRec() {}
   
   MLogRec(const MLogRec &right)
   {
	strcpy(logname,right.logname);
	strcpy(logip,right.logip);
	pid = right.pid;
	logintime = right.logintime;
	logouttime = right.logouttime;
	logtime = right.logtime;
   }

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
};

struct Msg
{
	enum MsgType type;
	struct	
	{
		MRegister reg;
		MLogin login;
		MLogRec logdata;
	} data;
};

#endif
