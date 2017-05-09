#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T14:41:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Family_tree
TEMPLATE = app


SOURCES +=    Source/family.cpp \
    Source/main.cpp \
    Source/mainwindow.cpp \
    Source/person.cpp \
    Source/treeleaf.cpp \
    Source/view.cpp \
    Source/widget.cpp

HEADERS  +=    Source/family.h \
    Source/mainwindow.h \
    Source/person.h \
    Source/treeleaf.h \
    Source/view.h \
    Source/widget.h

RESOURCES += \
    Resource/resources.qrc
