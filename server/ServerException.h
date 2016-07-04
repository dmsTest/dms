#ifndef SERVEREXCEPTION_H
#define SERVEREXCEPTION_H
#include <exception>
#include <string>
#include <iostream>


class ServerException : public std::exception
{
public:
    ServerException();
    ServerException(const std::string &str);
    virtual ~ServerException();
private:
    std::string m_msg;

};

class SocketException : public ServerException
{
public:
    SocketException();
    SocketException(const std::string &str);
};

class DBException : public ServerException
{
public:
    DBException();
    DBException(const std::string &str);
};


class ThreadException : public ServerException
{
public:
    ThreadException();
    ThreadException(const std::string &str);
};

#endif // SERVEREXCEPTION_H
