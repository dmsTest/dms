#ifndef CLIENTEXCEPTION_H
#define CLIENTEXCEPTION_H

#include <exception>
#include <string>
#include <iostream>

class ClientException : public std::exception
{
	public:
		    ClientException();
		    ClientException(const std::string &str);
		    virtual const char* what() ;
		    virtual ~ClientException() throw();
	private:
            std::string m_msg;

};

class BackupException : public ClientException
{
	public:
		    BackupException();
		    BackupException(const std::string &str);

};

class SocketException : public ClientException
{
	public:
		    SocketException();
		        SocketException(const std::string &str);

};

class ReadException : public ClientException
{
	public:
		    ReadException();
		        ReadException(const std::string &str);

};

class SendException : public ClientException
{
	public:
		    SendException();
		        SendException(const std::string &str);

};

class SaveException : public ClientException
{
	public:
		    SaveException();
		        SaveException(const std::string &str);

};

#endif // CLIENTEXCEPTION_H

