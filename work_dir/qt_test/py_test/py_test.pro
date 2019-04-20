#-------------------------------------------------
#
# Project created by QtCreator 2019-04-20T02:45:52
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = py_test
CONFIG   += console
CONFIG   -= app_bundle

LIBS += -lpython2.7
QMAKE_CXXFLAGS += -std=c++11
TEMPLATE = app


SOURCES += main.cpp \
    py_wrap.cpp

HEADERS += \
    py_wrap.h
