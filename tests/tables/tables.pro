#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T20:35:07
#
#-------------------------------------------------
include(../tests.pri)

QT       += sql testlib

QT       -= gui

TARGET = tst_tables
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_tables.cpp \
    ../models.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../models.h
