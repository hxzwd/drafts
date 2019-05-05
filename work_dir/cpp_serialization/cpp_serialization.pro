
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    c_serializable.cpp \
    c_string_wrap.cpp \
    c_test_class.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    c_serializable.hpp \
    c_string_wrap.hpp \
    c_test_class.hpp

