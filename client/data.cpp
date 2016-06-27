//数据对象类型定义
#ifdef _DATA_H
#define _DATA_H
#include<unistd.h>//pid_t等uc数据类型和函数
//test ljm
//登入登出日志记录
struct LogRec
{
   char logname[32];     //登入名
   char logip[32];       //登入ip
   pid_t pid;            //登入进程号
   long logtime;         //登入或登出时间
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
};

#endif
