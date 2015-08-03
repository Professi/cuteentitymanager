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
    src/cache.h \
    src/entityhelper.h \
    src/logger.h \
    src/query.h \
    src/join.h \
    src/queryinterpreter.h \
    src/condition.h

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
    src/cache.cpp \
    src/entityhelper.cpp \
    src/logger.cpp \
    src/query.cpp \
    src/join.cpp \
    src/queryinterpreter.cpp \
    src/condition.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
    QMAKE_CXXFLAGS += -Wall -Wextra -Wmaybe-uninitialized -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wunsafe-loop-optimizations -pedantic -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wunreachable-code -O
}
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14
#QMAKE_CXXFLAGS +=  -Winit-self
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
