#ifndef POST_H
#define POST_H

#include <QMainWindow>
#include "Client.h"
#include "LogReader.h"
#include "LogSender.h"
#include "data.h"

namespace Ui {
class post;
}

class post : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit post(QWidget *parent = 0);
    ~post();

    
private:
    Ui::post *ui;
    Client client;
    LogReader logreader;
    ConsoleSender consolesender;
    SocketSender socketsender;


private slots:
    void pushB1_clicked();
    void pushB2_clicked();

};

#endif // POST_H
