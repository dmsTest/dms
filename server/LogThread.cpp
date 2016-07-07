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
		char buf[sizeof(Msg)];
		int rel = recv(m_connfd, buf, sizeof(buf), 0);
		if(rel == 0)
			break;
		Msg item;
		memcpy(&item,buf,sizeof(buf));
		logqueue.push(m_connfd,item);
		++num;
	    }
	        std::cout << "recv: " << num << " !" << std::endl;
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
		std::pair<int,Msg> mlogrec;
		logqueue.pop(mlogrec);
		switch(mlogrec.second.type)
		{
		case REG:
		   {
			//register dynamic_cast
			MysqlDao *dao = dynamic_cast<MysqlDao*>(&m_dao);
			bool isInsert = dao->insertUser(mlogrec.second.data.reg);
			if(isInsert)
			{
				char buf[5] = "yes";
				send(mlogrec.first,buf,sizeof(buf),0);//ok
			}
			else
			{
				char buf[5] = "no";
				send(mlogrec.first,buf,sizeof(buf),0);//fail
			}
			break;
		   }
		case LOGIN:
		   {	
	   	   //login
			MysqlDao *dao = dynamic_cast<MysqlDao*>(&m_dao);
			bool isSuccess = dao->queryUser(mlogrec.second.data.login);
			if(isSuccess)
			{
				char buf[5] = "yes";
				send(mlogrec.first,buf,sizeof(buf),0);
			}//ok then send
			else
			{
				char buf[5] = "no";
				send(mlogrec.first,buf,sizeof(buf),0);
			}//fail then send
			break;
		   }
		case DATA:
		   {	
	   	   //data
			m_dao.insert(mlogrec.second.data.logdata);
			break;
		   }
		}
		/*
		if(strcmp(mlogrec.logname,"") != 0)
		{
			//-------need update-------
			m_dao.insert(mlogrec);
		}
		*/
	//std::cout << "----------end pop----------" << std::endl;
	}
}

