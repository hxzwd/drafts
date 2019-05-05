#-------------------------------------------------
#
# Project created by QtCreator 2019-05-05T18:07:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = cpp_tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    c_test_class.cpp \
    c_test_class_2.cpp

HEADERS += \
    c_test_class.h \
    c_test_class_2.h
