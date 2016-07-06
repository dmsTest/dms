#include "LogThread.h"
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <list>

LogThread::LogThread()
{
	    //ctor
	    //
}

void LogThread::start()
{
	pthread_t tid;
	int error=pthread_create(&tid,NULL,task,this);
	if(error)
	{
		 printf("%s\n",strerror(tid));
				        
   	}
}

void* LogThread::task(void* arg)
{
	LogThread *pThread = static_cast<LogThread*>(arg);
	pThread->run();
	return NULL; 
}

LogThread::~LogThread()
{
	    //dtor
	    //
}

ClientThread::ClientThread() : LogThread()       //ClientThread的构造函数
{
	

}

ClientThread::ClientThread(int connfd) : m_connfd(connfd)
{
	std::cout << "-------create clientthread-------" << std::endl;

}


void ClientThread::run() throw(ThreadException)
{
	//std::cout << "-----------accept data start------" << std::endl;
	int num = 0;
	    while(1)
	    {
		  //  std::cout << "-------accept data--------" << std::endl;
		//7. 接收数据
		char buf[sizeof(MLogRec)];
		recv(m_connfd, buf, sizeof(buf), 0);
		if(!strcmp(buf, "BYE"))
			break;
		MLogRec item;
		memcpy(&item,buf,sizeof(buf));
		logqueue.push(item);
		++num;
	    }
	        std::cout << "recv data: " << num << " !" << std::endl;
}

ClientThread::~ClientThread()
{
	close(m_connfd);
}

StoreThread::StoreThread(LogDao& dao) : LogThread(),m_dao(dao)   //StoreThread的构造函数
{
	

}

StoreThread::~StoreThread()
{
	

}

void StoreThread::run() throw(ThreadException)
{
	std::cout << "---------store thread run----------" << std::endl;
	while(true)
	{
	//std::cout << "----------start pop--------" << std::endl;
		MLogRec mlogrec;
		logqueue.pop(mlogrec);
		if(strcmp(mlogrec.logname,"") != 0)
		{
			m_dao.insert(mlogrec);
		}
	//std::cout << "----------end pop----------" << std::endl;
	}
}

