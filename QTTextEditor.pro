#-------------------------------------------------
#
# Project created by QtCreator 2013-04-20T13:05:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTTextEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filehandler.cpp \
    highlighter.cpp \
    file.cpp

HEADERS  += mainwindow.h \
    filehandler.h \
    highlighter.h \
    file.h

FORMS    += mainwindow.ui
