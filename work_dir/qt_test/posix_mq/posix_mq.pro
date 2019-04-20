#-------------------------------------------------
#
# Project created by QtCreator 2019-04-20T08:06:29
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = posix_mq
CONFIG   += console
CONFIG   -= app_bundle


LIBS += -lrt -lnsl -lpthread
QMAKE_CXXFLAGS += -std=c++11


TEMPLATE = app


SOURCES += main.cpp \
    posix_mq.cpp

HEADERS += \
    posix_mq.h
