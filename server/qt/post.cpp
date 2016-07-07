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

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

post::post(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::post)
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
//    QFile *file=new QFile("./longin_li/test.txt");
//    file->open(QIODevice::ReadOnly);
//    QString data = QString(file->readAll());


    QFile file("test.txt");
    //QFile file("wtmpx");
    QTextCodec *codec= QTextCodec::codecForName("GBK");
   if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
       QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
       QMessageBox::warning(this,tr("error"),tr("Can't open the file!"),QMessageBox::Yes);
   }
   while(!file.atEnd())
   {
       //QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );



       QByteArray all = file.readAll();
       QString str=codec->toUnicode(all);
       QStringList user;

       user<<str;

       QStringListModel *model = new QStringListModel(user);
       model->setStringList(user);

       //ui->listView->setSelection(user.size()-1);
       //ui->listView->scrollTo(200,200);

       ui->listView->setModel(model);
       ui->listView->setUpdatesEnabled(true);
       //ui->listView->lineWidth(311);



       //sleep(1);
   }
}

void post::pushB2_clicked()
{
    this->close();
}



