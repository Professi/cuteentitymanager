#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T20:35:07
#
#-------------------------------------------------
include(../tests.pri)

QT       += sql testlib

QT       -= gui

TARGET = tst_em
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_em.cpp \
    ../models.cpp \
    main.cpp \
    tst_querybuilder.cpp \
    ../model/testpupilchild.cpp \
    ../model/testpupilgrandchild.cpp \
    ../model/testpupilgreatgrandchild.cpp \
    ../model/testperson.cpp \
    ../model/testgroup.cpp \
    ../model/testpupil.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../models.h \
    tst_em.h \
    tst_querybuilder.h \
    ../model/testpupilchild.h \
    ../model/testpupilgrandchild.h \
    ../model/testpupilgreatgrandchild.h \
    ../model/testperson.h \
    ../model/testgroup.h \
    ../model/testpupil.h
