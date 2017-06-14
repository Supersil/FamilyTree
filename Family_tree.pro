#-------------------------------------------------
#
# Project created by QtCreator 2017-06-04T11:27:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Family_tree
TEMPLATE = app


SOURCES +=  Source/family.cpp \
    Source/info.cpp \
    Source/main.cpp \
    Source/mainwindow.cpp \
    Source/person.cpp \
    Source/treeleaf.cpp \
    Source/view.cpp \
    Source/treestructure.cpp

HEADERS  += \
    Source/family.h \
    Source/info.h \
    Source/mainwindow.h \
    Source/person.h \
    Source/treeleaf.h \
    Source/view.h \
    treestructure.h \
    Source/treestructure.h

RESOURCES += \
    Resource/resources.qrc

DISTFILES += \
    README.md

QMAKE_CXXFLAGS += -std=c++11

