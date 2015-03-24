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
    src/schema.h \
    src/schema/sqliteschema.h \
    src/tableschema.h \
    src/columnschema.h \
    src/schema/pgsqlschema.h \
    src/schema/mysqlschema.h

SOURCES += \
src/entity.cpp \
    src/entitymanager.cpp \
    src/database.cpp \
    src/schema.cpp \
    src/schema/sqliteschema.cpp \
    src/tableschema.cpp \
    src/columnschema.cpp \
    src/schema/pgsqlschema.cpp \
    src/schema/mysqlschema.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
CONFIG += c++11
