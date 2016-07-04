#include "ServerException.h"

ServerException::ServerException():m_msg("server is exception!")

{

}

ServerException::ServerException(const std::string &str) :m_msg("server is exception!")
{

    m_msg = m_msg + " " + str + "!";

}

ServerException::~ServerException()
{


}

SocketException::SocketException() : ServerException("Socket error")
{


}

SocketException::SocketException(const std::string &str) : ServerException(str)
{


}


DBException::DBException() : ServerException("DB error")
{


}

DBException::DBException(const std::string &str) : ServerException(str)
{


}

ThreadException::ThreadException() : ServerException("Thread error")
{


}

ThreadException::ThreadException(const std::string &str) : ServerException(str)
{


}
