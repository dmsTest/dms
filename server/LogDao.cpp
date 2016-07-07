#include "LogDao.h"

LogDao::LogDao()
{
    //ctor
}

LogDao::~LogDao()
{
    //dtor
}

FileDao::FileDao(const std::string& path) : m_ofs(path.c_str(),std::ofstream::out | std::ofstream::app)
{

}

FileDao::~FileDao()
{
	m_ofs.close();
}

void FileDao::insert(const MLogRec& log) throw(DBException)
{
	m_ofs << log.logname << " " << log.logip << " " << log.pid 
				<< " " << log.logintime << " " << log.logouttime << " " 
					<< log.logtime << std::endl;
}

MysqlDao::MysqlDao(const std::string &username, const std::string &passwd)
{
	driver = get_driver_instance();
    con = driver->connect("tcp://localhost:3306","root","123456");
    con->setSchema("dms");	//connect to the dms database    
}

std::string MysqlDao::getStringFromLong(long long_time)
{
	time_t now_time = long_time;
	struct tm *now_tm;
	now_tm = localtime(&now_time);
	char arr[20];
	sprintf(arr,"%04d-%02d-%02d %02d:%02d:%02d",now_tm->tm_year+1900,now_tm->tm_mon+1,now_tm->tm_mday,now_tm->tm_hour,now_tm->tm_min,now_tm->tm_sec);
	std::string str(arr);
	return str;
}

std::string MysqlDao::getStringFromTime(long long_time)
{
	int hour,min,sec,temp;
	hour = long_time/3600;
	temp = long_time%3600;
	min = temp/60;
	sec = temp%60;
	char arr[10];
	sprintf(arr,"%02d:%02d:%02d",hour,min,sec);
	std::string str(arr);
	return str;	
}

void MysqlDao::insert(const MLogRec& log) throw(DBException)
{
	pstmt = con->prepareStatement("insert into data (username,logname,logip,pid,logintime,logouttime,logtime) values(?,?,?,?,?,?,?)");
	pstmt->setString(1,"admin");
	pstmt->setString(2,log.logname);
	pstmt->setString(3,log.logip);
	pstmt->setInt(4,log.pid);
	pstmt->setString(5,getStringFromLong(log.logintime));
	pstmt->setString(6,getStringFromLong(log.logouttime));
	pstmt->setString(7,getStringFromTime(log.logtime));
	bool is_success = pstmt->executeUpdate();
	if(is_success)
		;	//std::cout << "insert success!" << std::endl;
	else
		std::cout << "inset fail!" << std::endl;
}

bool MysqlDao::queryUser(MLogin login)
{
	pstmt = con->prepareStatement("select password from user where username=?");
	pstmt->setString(1,login.username);
	sql::ResultSet *rs = pstmt->executeQuery();
	bool isTrue = false;
	while(rs->next())
	{
		if(strcmp(login.password,rs->getString(1).c_str())==0)
		{
			isTrue = true;
		}
	}
	delete rs;
	return isTrue;
}

bool MysqlDao::insertUser(MRegister reg)
{
	pstmt = con->prepareStatement("insert into user (username,password,gender,phone) values(?,?,?,?)");
	pstmt->setString(1,reg.username);
	pstmt->setString(2,reg.password);
	pstmt->setString(3,reg.gender);
	pstmt->setString(4,reg.phone);
	return pstmt->executeUpdate();
}

MysqlDao::~MysqlDao()
{
	delete pstmt;
	con->close();
	delete con;
}
