/********************************************************************************
** Form generated from reading UI file 'lregister.ui'
**
** Created: Mon Jul 4 16:57:23 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LREGISTER_H
#define UI_LREGISTER_H

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
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lregister
{
public:
    QWidget *centralwidget;
    QRadioButton *radioButton;
    QLabel *label4;
    QLabel *label5;
    QLineEdit *lineEdit1;
    QLabel *label2;
    QLineEdit *lineEdit2;
    QPushButton *pushButton_2;
    QLabel *label6;
    QLineEdit *lineEdit3;
    QPushButton *pushButton;
    QRadioButton *radioButton_2;
    QLineEdit *lineEdit4;
    QLabel *label3;
    QLabel *label1;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Lregister)
    {
        if (Lregister->objectName().isEmpty())
            Lregister->setObjectName(QString::fromUtf8("Lregister"));
        Lregister->resize(621, 473);
        centralwidget = new QWidget(Lregister);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(240, 250, 91, 22));
        QFont font;
        font.setFamily(QString::fromUtf8("Tlwg Typist"));
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        radioButton->setFont(font);
        label4 = new QLabel(centralwidget);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(130, 250, 101, 31));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label4->setFont(font1);
        label5 = new QLabel(centralwidget);
        label5->setObjectName(QString::fromUtf8("label5"));
        label5->setGeometry(QRect(100, 300, 111, 41));
        label5->setFont(font1);
        lineEdit1 = new QLineEdit(centralwidget);
        lineEdit1->setObjectName(QString::fromUtf8("lineEdit1"));
        lineEdit1->setGeometry(QRect(240, 80, 211, 27));
        label2 = new QLabel(centralwidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(110, 130, 131, 31));
        label2->setFont(font1);
        lineEdit2 = new QLineEdit(centralwidget);
        lineEdit2->setObjectName(QString::fromUtf8("lineEdit2"));
        lineEdit2->setGeometry(QRect(240, 130, 211, 27));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(450, 380, 98, 27));
        label6 = new QLabel(centralwidget);
        label6->setObjectName(QString::fromUtf8("label6"));
        label6->setGeometry(QRect(180, -10, 241, 71));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\346\255\243\351\273\221"));
        font2.setPointSize(48);
        label6->setFont(font2);
        lineEdit3 = new QLineEdit(centralwidget);
        lineEdit3->setObjectName(QString::fromUtf8("lineEdit3"));
        lineEdit3->setGeometry(QRect(240, 190, 211, 27));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(320, 380, 98, 27));
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(350, 250, 116, 22));
        radioButton_2->setFont(font);
        lineEdit4 = new QLineEdit(centralwidget);
        lineEdit4->setObjectName(QString::fromUtf8("lineEdit4"));
        lineEdit4->setGeometry(QRect(240, 310, 211, 27));
        label3 = new QLabel(centralwidget);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(40, 190, 211, 31));
        label3->setFont(font1);
        label1 = new QLabel(centralwidget);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(110, 80, 131, 31));
        label1->setFont(font1);
        Lregister->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Lregister);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 621, 26));
        Lregister->setMenuBar(menubar);
        statusbar = new QStatusBar(Lregister);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Lregister->setStatusBar(statusbar);
        toolBar = new QToolBar(Lregister);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        Lregister->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(Lregister);

        QMetaObject::connectSlotsByName(Lregister);
    } // setupUi

    void retranslateUi(QMainWindow *Lregister)
    {
        Lregister->setWindowTitle(QApplication::translate("Lregister", "MainWindow", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("Lregister", "male", 0, QApplication::UnicodeUTF8));
        label4->setText(QApplication::translate("Lregister", "gender", 0, QApplication::UnicodeUTF8));
        label5->setText(QApplication::translate("Lregister", "telephone", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("Lregister", "password", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Lregister", "back", 0, QApplication::UnicodeUTF8));
        label6->setText(QApplication::translate("Lregister", "Register", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Lregister", "sumbit", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("Lregister", "female", 0, QApplication::UnicodeUTF8));
        label3->setText(QApplication::translate("Lregister", "repeat password", 0, QApplication::UnicodeUTF8));
        label1->setText(QApplication::translate("Lregister", "username", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("Lregister", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Lregister: public Ui_Lregister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LREGISTER_H
