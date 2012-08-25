#-------------------------------------------------
#
# Project created by QtCreator 2012-08-25T18:05:24
#
#-------------------------------------------------

QT       += core gui xml

TARGET = qtxmldiffer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmldiffer.cpp \
    3rdpart/treemodel.cpp \
    3rdpart/treeitem.cpp

HEADERS  += mainwindow.h \
    xmldiffer.h \
    3rdpart/treemodel.h \
    3rdpart/treeitem.h

FORMS    += mainwindow.ui

INCLUDEPATH += 3rdpart
