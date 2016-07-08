#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T08:50:08
#
#-------------------------------------------------

QT       += core gui

TARGET = login_li
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    post.cpp \
    lregister.cpp \
    LogSender.cpp \
    LogReader.cpp \
    ClientException.cpp \
    Client.cpp \
    data.cpp

HEADERS  += mainwindow.h \
    post.h \
    lregister.h \
    LogSender.h \
    LogReader.h \
    ClientException.h \
    Client.h \
    data.h

FORMS    += mainwindow.ui \
    post.ui \
    lregister.ui

RESOURCES += \
    lcy.qrc

OTHER_FILES += \
    backup
