#-------------------------------------------------
#
# Project created by QtCreator 2019-04-14T00:33:40
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = onc_rpc_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lnsl

SOURCES += main.cpp \
    client.c \
    hello_clnt.c

HEADERS += \
    hello.h
