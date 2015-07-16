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
    src/schema/pgsqlschema.h \
    src/schema/mysqlschema.h \
    src/databasemigration.h \
    src/querybuilder.h \
    src/schema/sqlitequerybuilder.h \
    src/relation.h \
    src/entityinstancefactory.h \
    src/condition.h \
    src/cache.h

SOURCES += \
src/entity.cpp \
    src/entitymanager.cpp \
    src/database.cpp \
    src/schema.cpp \
    src/schema/sqliteschema.cpp \
    src/tableschema.cpp \
    src/schema/pgsqlschema.cpp \
    src/schema/mysqlschema.cpp \
    src/databasemigration.cpp \
    src/querybuilder.cpp \
    src/schema/sqlitequerybuilder.cpp \
    src/relation.cpp \
    src/entityinstancefactory.cpp \
    src/condition.cpp \
    src/cache.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
CONFIG += c++14
