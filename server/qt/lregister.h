#ifndef LREGISTER_H
#define LREGISTER_H

#include <QMainWindow>




namespace Ui {
class Lregister;

}

class Lregister : public QMainWindow
{
    Q_OBJECT




public:
    explicit Lregister(QWidget *parent = 0);
    ~Lregister();
    
private:
    Ui::Lregister *ui;



private slots:
    void pB2_clicked();
    void pB1_clicked();
};


#endif // LREGISTER_H
