#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "post.h"
#include "lregister.h"

namespace Ui {
    class MainWindow;
}

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);


private:
    Ui::MainWindow *ui;
    post p;
    Lregister lr;


private slots:
    void pB2_clicked();
    void pB1_clicked();
};

#endif
