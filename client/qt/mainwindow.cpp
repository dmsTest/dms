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
  if(this->ui->lE1->text().trimmed()== tr("1") &&
     this->ui->lE2->text().trimmed()==tr("1"))
  {

        p.show();
  }
  else
  {
      QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
      QMessageBox::critical(this,tr("error"),tr("Incorrect username or password!"),QMessageBox::Yes);
      this->ui->lE1->clear();
      this->ui->lE2->clear();
      this->ui->lE1->setFocus();//将光标移到用户名输入框
  }
}

void MainWindow::pB2_clicked()
{
    lr.show();
}

