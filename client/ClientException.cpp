#include "ClientException.h"

ClientException::ClientException()
{
	    //ctor
	    //
}

ClientException::ClientException(const std::string &str) : m_msg(str)
{
	    //ctor
	    //
}

const char*  ClientException::what()
{
	    return m_msg.c_str();

}
ClientException::~ClientException()
{
	    //dtor
	    //
}

BackupException::BackupException() : ClientException()
{
	

}

BackupException::BackupException(const std::string &str) : ClientException(str)
{
	

}

SocketException::SocketException() : ClientException()
{
	

}

SocketException::SocketException(const std::string &str) : ClientException(str)
{
	

}

ReadException::ReadException()
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

SaveException::SaveException() : ClientException()
{
	

}

SaveException::SaveException(const std::string &str) : ClientException(str)
{
	

}

