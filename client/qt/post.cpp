#include "post.h"
#include "ui_post.h"
#include <QStringList>
#include<QStringListModel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <qtextcodec.h>
#include <qlistview.h>
#include <list>
#include <iostream>
#include <stdio.h>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

std::string logFile = "wtmpx";
std::string loginsFile = "logins.dat";
std::string _ip = "127.0.0.1";
short _port = 8888;
list<MLogRec>logList_temp;
post::post(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::post),logreader(logFile,loginsFile),
    consolesender(),socketsender("./fail.dat",_port,_ip),
    client(logreader,socketsender)
{
    ui->setupUi(this);
    setWindowTitle("Send");
    connect(ui->pushB1, SIGNAL(clicked()),this, SLOT(pushB1_clicked()));
    connect(ui->pushB2, SIGNAL(clicked()),this, SLOT(pushB2_clicked()));
}

post::~post()
{
    delete ui;
}

void post::pushB1_clicked()
{
    logList_temp= client.getloglist();
    list<MLogRec>::iterator it=logList_temp.begin();
    while(it!=logList_temp.end()){
        QString str1(it->logname);
        QString str2(it->logip);
        int pid=it->pid;
        QString str3(QString::number(pid));
        long logintime=it->logintime;
        QString str4(QString::number(logintime));
        long logouttime=it->logouttime;
        QString str5(QString::number(logouttime));
        long logtime=it->logtime;
        QString str6(QString::number(logtime));
        QString str=str1+"  "+str2+"  "+str3+"  "+str4+"  "+str5+"  "+str6+'\n';
        ui->textEdit->append(str);
        it++;
    }
    ui->textEdit->append("***************************Send data over!***********************");
    ui->textEdit->append("total:"+QString::number(logList_temp.size()));
    client.dataMine();
}

void post::pushB2_clicked()
{
    this->close();
}



