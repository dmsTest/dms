//数据对象类型定义
#ifndef _DATA_H
#define _DATA_H
#include<unistd.h>//pid_t等uc数据类型和函数

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

