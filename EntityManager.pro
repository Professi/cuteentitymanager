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
src/base/entity.h \
    src/base/entitymanager.h \
    src/base/enums/persistencetype.h \
    src/base/database.h \
    src/base/enums/databasetype.h \
    src/models/artikel.h \
    src/base/enums/relationtype.h \
    src/base/relation.h

SOURCES += main.cpp \
src/base/entity.cpp \
    src/base/entitymanager.cpp \
    src/base/database.cpp \
    src/models/artikel.cpp \
    src/base/relation.cpp
