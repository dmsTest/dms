/********************************************************************************
** Form generated from reading UI file 'post.ui'
**
** Created: Mon Jul 4 16:57:23 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POST_H
#define UI_POST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_post
{
public:
    QWidget *centralwidget;
    QPushButton *pushB1;
    QPushButton *pushB2;
    QListView *listView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *post)
    {
        if (post->objectName().isEmpty())
            post->setObjectName(QString::fromUtf8("post"));
        post->resize(657, 528);
        centralwidget = new QWidget(post);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushB1 = new QPushButton(centralwidget);
        pushB1->setObjectName(QString::fromUtf8("pushB1"));
        pushB1->setGeometry(QRect(20, 130, 111, 41));
        pushB2 = new QPushButton(centralwidget);
        pushB2->setObjectName(QString::fromUtf8("pushB2"));
        pushB2->setGeometry(QRect(20, 250, 111, 41));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(140, 20, 451, 501));
        listView->setLayoutDirection(Qt::LeftToRight);
        listView->setAutoFillBackground(true);
        listView->setSpacing(0);
        listView->setWordWrap(true);
        listView->setSelectionRectVisible(true);
        post->setCentralWidget(centralwidget);
        menubar = new QMenuBar(post);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 657, 26));
        post->setMenuBar(menubar);
        statusbar = new QStatusBar(post);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        post->setStatusBar(statusbar);

        retranslateUi(post);

        QMetaObject::connectSlotsByName(post);
    } // setupUi

    void retranslateUi(QMainWindow *post)
    {
        post->setWindowTitle(QApplication::translate("post", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushB1->setText(QApplication::translate("post", "Send", 0, QApplication::UnicodeUTF8));
        pushB2->setText(QApplication::translate("post", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class post: public Ui_post {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POST_H
