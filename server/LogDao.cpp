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

void MysqlDao::insert(const MLogRec& log) throw(DBException)
{
	pstmt = con->prepareStatement("insert into data (logname,logip,pid,logintime,logouttime,logtime) values(?,?,?,?,?,?)");
	pstmt->setString(1,log.logname);
	pstmt->setString(2,log.logip);
	pstmt->setInt(3,log.pid);
	pstmt->setString(4,converTToString<long>(log.logintime));
	pstmt->setString(5,converTToString<long>(log.logouttime));
	pstmt->setString(6,converTToString<long>(log.logtime));
	bool is_success = pstmt->executeUpdate();
	if(is_success)
		;	//std::cout << "insert success!" << std::endl;
	else
		std::cout << "inset fail!" << std::endl;
}

MysqlDao::~MysqlDao()
{
	delete pstmt;
	con->close();
	delete con;
}
