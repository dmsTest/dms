#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextCodec>
#include"qpainter.h"
#include"post.h"
#include"lregister.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    setWindowTitle("Login");
    ui->lE2->setEchoMode(QLineEdit::Password);  //设置为小黑点

    ui->label->setStyleSheet(QString("color:red"));
    ui->label2->setStyleSheet(QString("color:blue"));
    ui->label3->setStyleSheet(QString("color:blue"));

    ui->pB1->setStyleSheet(QString("color:green"));
    ui->pB2->setStyleSheet(QString("color:green"));
    connect(ui->pB1, SIGNAL(clicked()),this, SLOT(pB1_clicked()));
    connect(ui->pB2, SIGNAL(clicked()),this, SLOT(pB2_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void MainWindow::pB1_clicked()
{
    std::string username = this->ui->lE1->text().toStdString();
    std::string password = this->ui->lE2->text().toStdString();
    extern SocketSender socketSender;
    extern Msg msg;
    msg.type = LOGIN;
    strcpy(msg.data.login.username,username.c_str());
    strcpy(msg.data.login.password,password.c_str());
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
    else
    {
        p.show();
        this->close();
    }
}

void MainWindow::pB2_clicked()
{
    lr.show();
    this->close();
}

