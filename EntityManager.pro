#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T15:03:24
#
#-------------------------------------------------

QT       += core
QT       += sql
QT       -= gui

TARGET = CuteEntityManager
TEMPLATE = lib

DEFINES += CUTE_ENTITY_MANAGER_LIBRARY

HEADERS += \
src/entity.h \
    src/entitymanager.h \
    src/database.h \
    src/enums/databasetype.h \
    src/schema.h

SOURCES += \
src/base/entity.cpp \
    src/entitymanager.cpp \
    src/database.cpp \
    src/schema.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
