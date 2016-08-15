#-------------------------------------------------
#
# Project created by QtCreator 2014-02-11T15:48:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MineSweeper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pushbutton.cpp \
    detect.cpp \
    autowork.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    pushbutton.h \
    create.h \
    map.h \
    detect.h \
    autowork.h \
    settings.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc

RC_FILE = mineicon.rc
