#include "ClientException.h"

ClientException::ClientException():m_msg("client is exception!")
{
	    //ctor
	    //
}

ClientException::ClientException(const std::string &str) : m_msg("client is exception")
{
	    m_msg = m_msg + " " + str + "!";
}

const char*  ClientException::what()
{
	    return m_msg.c_str();

}

ClientException::~ClientException() throw()
{
	    //dtor
	    //
}

BackupException::BackupException() : ClientException("backup error")
{
	

}

BackupException::BackupException(const std::string &str) : ClientException(str)
{
	

}

SocketException::SocketException() : ClientException("Socket error")
{
	

}

SocketException::SocketException(const std::string &str) : ClientException(str)
{
	

}

ReadException::ReadException() : ClientException("read error")
{
	

}

ReadException::ReadException(const std::string &str) : ClientException(str)
{
	

}

SendException::SendException() : ClientException()
{
	

}

SendException::SendException(const std::string &str) : ClientException(str)
{
	

}

SaveException::SaveException() : ClientException("save error")
{
	

}

SaveException::SaveException(const std::string &str) : ClientException(str)
{
	

}

