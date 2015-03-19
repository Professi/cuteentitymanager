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
src/entity.h \
    src/entitymanager.h \
    src/enums/persistencetype.h \
    src/database.h \
    src/enums/databasetype.h \
    src/enums/relationtype.h \
    src/relation.h

SOURCES += \
src/base/entity.cpp \
    src/entitymanager.cpp \
    src/database.cpp \
    src/relation.cpp
