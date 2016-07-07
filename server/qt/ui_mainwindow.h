/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Jul 4 16:57:23 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *mainWindow;
    QLineEdit *lE1;
    QLineEdit *lE2;
    QLabel *label;
    QLabel *label2;
    QLabel *label3;
    QPushButton *pB1;
    QPushButton *pB2;
    QFrame *frame;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(648, 441);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        mainWindow = new QWidget(MainWindow);
        mainWindow->setObjectName(QString::fromUtf8("mainWindow"));
        mainWindow->setStyleSheet(QString::fromUtf8(""));
        lE1 = new QLineEdit(mainWindow);
        lE1->setObjectName(QString::fromUtf8("lE1"));
        lE1->setGeometry(QRect(340, 140, 113, 27));
        lE2 = new QLineEdit(mainWindow);
        lE2->setObjectName(QString::fromUtf8("lE2"));
        lE2->setGeometry(QRect(340, 190, 113, 27));
        label = new QLabel(mainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(240, 10, 191, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\346\255\243\351\273\221"));
        font.setPointSize(50);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label2 = new QLabel(mainWindow);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(190, 140, 131, 31));
        QFont font1;
        font1.setPointSize(20);
        label2->setFont(font1);
        label3 = new QLabel(mainWindow);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(190, 190, 131, 21));
        label3->setFont(font1);
        pB1 = new QPushButton(mainWindow);
        pB1->setObjectName(QString::fromUtf8("pB1"));
        pB1->setGeometry(QRect(220, 260, 98, 27));
        pB2 = new QPushButton(mainWindow);
        pB2->setObjectName(QString::fromUtf8("pB2"));
        pB2->setGeometry(QRect(340, 260, 98, 27));
        frame = new QFrame(mainWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, -10, 731, 431));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/lcy/c.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pB2->raise();
        MainWindow->setCentralWidget(mainWindow);
        frame->raise();
        lE1->raise();
        lE2->raise();
        label->raise();
        label2->raise();
        label3->raise();
        pB1->raise();
        pB2->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 648, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("MainWindow", "Username", 0, QApplication::UnicodeUTF8));
        label3->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        pB1->setText(QApplication::translate("MainWindow", "Submit", 0, QApplication::UnicodeUTF8));
        pB2->setText(QApplication::translate("MainWindow", "register", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
