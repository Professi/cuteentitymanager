#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T15:03:24
#
#-------------------------------------------------

QT       += core
QT       += sql

QT       -= gui

TARGET = EntityManager
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    models/artikel.h \
    models/person.h \
    models/group.h

SOURCES += \
    main.cpp \
    models/artikel.cpp \
    models/person.cpp \
    models/group.cpp

unix:!macx: LIBS += -L$$PWD/../../build-EntityManager-Desktop-Debug -lCuteEntityManager
INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src
CONFIG += c++11
