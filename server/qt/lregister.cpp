#include "lregister.h"
#include "ui_lregister.h"

#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <qtextcodec.h>
#include <QDebug>

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
}

void Lregister::pB2_clicked()
{
    close();
}

