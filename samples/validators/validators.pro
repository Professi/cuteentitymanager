#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T15:03:24
#
#-------------------------------------------------
include(../samples.pri)
QT       += core
QT       += sql

QT       -= gui

#TARGET = EntityManager
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    address.h \
    person.h

SOURCES += \
    main.cpp \
    address.cpp \
    person.cpp
