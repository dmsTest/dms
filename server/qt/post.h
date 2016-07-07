#ifndef POST_H
#define POST_H

#include <QMainWindow>

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

private slots:
    void pushB1_clicked();
    void pushB2_clicked();

};

#endif // POST_H
