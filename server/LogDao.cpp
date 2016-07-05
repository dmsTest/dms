#include "LogDao.h"

LogDao::LogDao()
{
    //ctor
}

LogDao::~LogDao()
{
    //dtor
}

FileDao::FileDao(const std::string& path) : m_ofs(path,ios::app)
{

}

FileDao::~FileDao()
{

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
	pstmt = con->prepareStatement("insert into data values(?,?,?,?,?,?)");
	pstmt->setString(1,log.logname);
	pstmt->setString(2,log.logip);
	pstmt->setInt(3,log.pid);
	pstmt->setBigInt(4,log.logintime);
	pstmt->setBigInt(5,log.logouttime);
	pstmt->setBigInt(6,log.logtime);
	bool is_success = pstmt->executeUpdate();
	if(is_success)
		std::cout << "insert success!" << std::endl;
	else
		std::cout << "inset fail!" << std::endl;
}

MysqlDao::~MysqlDao()
{
	delete pstmt;
	con.close();
	delete con;
	delete driver;
}
