/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created: Mon Jul 4 15:55:15 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_register
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit2;
    QLabel *label1;
    QRadioButton *radioButton_2;
    QLineEdit *lineEdit4;
    QLineEdit *lineEdit3;
    QLineEdit *lineEdit1;
    QLabel *label3;
    QLabel *label6;
    QLabel *label4;
    QLabel *label2;
    QRadioButton *radioButton;
    QLabel *label5;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *register)
    {
        if (register->objectName().isEmpty())
            register->setObjectName(QString::fromUtf8("register"));
        register->resize(537, 472);
        centralwidget = new QWidget(register);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 390, 98, 27));
        lineEdit2 = new QLineEdit(centralwidget);
        lineEdit2->setObjectName(QString::fromUtf8("lineEdit2"));
        lineEdit2->setGeometry(QRect(210, 140, 211, 27));
        label1 = new QLabel(centralwidget);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(80, 90, 131, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label1->setFont(font);
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(320, 260, 116, 22));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Tlwg Typist"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        radioButton_2->setFont(font1);
        lineEdit4 = new QLineEdit(centralwidget);
        lineEdit4->setObjectName(QString::fromUtf8("lineEdit4"));
        lineEdit4->setGeometry(QRect(210, 320, 211, 27));
        lineEdit3 = new QLineEdit(centralwidget);
        lineEdit3->setObjectName(QString::fromUtf8("lineEdit3"));
        lineEdit3->setGeometry(QRect(210, 200, 211, 27));
        lineEdit1 = new QLineEdit(centralwidget);
        lineEdit1->setObjectName(QString::fromUtf8("lineEdit1"));
        lineEdit1->setGeometry(QRect(210, 90, 211, 27));
        label3 = new QLabel(centralwidget);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(10, 200, 211, 31));
        label3->setFont(font);
        label6 = new QLabel(centralwidget);
        label6->setObjectName(QString::fromUtf8("label6"));
        label6->setGeometry(QRect(150, 0, 241, 71));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\346\255\243\351\273\221"));
        font2.setPointSize(48);
        label6->setFont(font2);
        label4 = new QLabel(centralwidget);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(100, 260, 101, 31));
        label4->setFont(font);
        label2 = new QLabel(centralwidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(80, 140, 131, 31));
        label2->setFont(font);
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(210, 260, 91, 22));
        radioButton->setFont(font1);
        label5 = new QLabel(centralwidget);
        label5->setObjectName(QString::fromUtf8("label5"));
        label5->setGeometry(QRect(70, 310, 111, 41));
        label5->setFont(font);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(420, 390, 98, 27));
        register->setCentralWidget(centralwidget);
        menubar = new QMenuBar(register);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 537, 26));
        register->setMenuBar(menubar);
        statusbar = new QStatusBar(register);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        register->setStatusBar(statusbar);

        retranslateUi(register);

        QMetaObject::connectSlotsByName(register);
    } // setupUi

    void retranslateUi(QMainWindow *register)
    {
        register->setWindowTitle(QApplication::translate("register", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("register", "sumbit", 0, QApplication::UnicodeUTF8));
        label1->setText(QApplication::translate("register", "username", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("register", "female", 0, QApplication::UnicodeUTF8));
        label3->setText(QApplication::translate("register", "repeat password", 0, QApplication::UnicodeUTF8));
        label6->setText(QApplication::translate("register", "Register", 0, QApplication::UnicodeUTF8));
        label4->setText(QApplication::translate("register", "gender", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("register", "password", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("register", "male", 0, QApplication::UnicodeUTF8));
        label5->setText(QApplication::translate("register", "telephone", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("register", "cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class register: public Ui_register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
