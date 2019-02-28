#-------------------------------------------------
#
# Project created by github/hilch
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = opcuademo1
TEMPLATE = app
CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    open62541.c \
    opcua_client.cpp \
    opcua_clientinternal.cpp \
    robotcontrol.cpp \
    mainwindowrobots.cpp

HEADERS  += mainwindow.h \
    open62541.h \
    opcua_client.h \
    opcua_clientinternal.h \
    robotcontrol.h

FORMS    += mainwindow.ui
QMAKE_CC= gcc -std=c99 -w
win32 {
LIBS += -lws2_32
}

RESOURCES += \
    resources.qrc

