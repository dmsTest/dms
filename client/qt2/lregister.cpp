#include "lregister.h"
#include "ui_lregister.h"

#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <qtextcodec.h>
#include <QDebug>
#include "LogSender.h"
Lregister::Lregister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lregister)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(pB1_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(pB2_clicked()));
}


Lregister::~Lregister()
{
    delete ui;
}

void Lregister::pB1_clicked()
{
    extern SocketSender socketSender;
    extern Msg msg;
    std::string username = this->ui->lineEdit1->text().toStdString();
    std::string password = this->ui->lineEdit2->text().toStdString();
    std::string repeatpasswd = this->ui->lineEdit3->text().toStdString();
    std::string gender = this->ui->radioButton->text().toStdString();
    std::string phonenum = this->ui->lineEdit4->text().toStdString();
    if(username.size()>=32||username.size()==0){
        QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
        QMessageBox::critical(this,tr("username unformat"),tr("username is unformat"),QMessageBox::Yes);
    }
    if(password.size()<=6||password.size()>=32||password!=repeatpasswd){
        QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
        QMessageBox::critical(this,tr("password unformat"),tr("password is error!"),QMessageBox::Yes);
    }
    if(strcmp(gender.c_str(),"male")==0)
    {
        gender = "男";
    }
    else
    {
        gender = "女";
    }
    if(phonenum.size()!=11){
        QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
        QMessageBox::critical(this,tr("phonenumber unformat"),tr("phonenumber is error,its length is 11!"),QMessageBox::Yes);
    }
    else if(username.size()>0&&username.size()<32&&password.size()>6&&password.size()<32&&password==repeatpasswd&&phonenum.size()==11){
        msg.type = REG;
        strcpy(msg.data.reg.username,username.c_str());
        strcpy(msg.data.reg.password,password.c_str());
        strcpy(msg.data.reg.gender,gender.c_str());
        strcpy(msg.data.reg.phone,phonenum.c_str());
        bool isSend = socketSender.sendData(msg);
        if(!isSend)
        {
            QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
            QMessageBox::critical(this,tr("connect error"),tr("connect server is error"),QMessageBox::Yes);
        }
        bool isSuccess = socketSender.recvData();
        if(!isSuccess)
        {
            QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
            QMessageBox::critical(this,tr("login error"),tr("name or password is error"),QMessageBox::Yes);
        }

    }


    /*
  if(ui->lineEdit2->text().length()<6
          )
  {
      //&& ui->lineEdit2->text()==ui->lineEdit3->text()&& ui->lineEdit4->text().length()=9
      QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
      QMessageBox::information(this,tr("success"),tr("Register success!"),QMessageBox::Yes);
      this->ui->lineEdit1->clear();
      this->ui->lineEdit2->clear();
      this->ui->lineEdit3->clear();
      this->ui->lineEdit4->clear();
      //this->ui->radioButton->;
      //this->ui->radioButton_2->clear();
      this->ui->lineEdit1->setFocus();//将光标移到用户名输入框
  }
  else
  {
      QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
      QMessageBox::critical(this,tr("error"),tr("Register fail!"),QMessageBox::Yes);

  }
  */
}

void Lregister::pB2_clicked()
{

    close();
}

