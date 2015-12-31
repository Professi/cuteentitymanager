include (../EntityManager.pri)
QT       += core
QT       += sql
#if you need Image Validation you must compile with += gui
#QT       += gui
QT       -= gui

TARGET = CuteEntityManager
TEMPLATE = lib
CONFIG += $$EM_LIBRARY_TYPE
VERSION = $$EM_VERSION

HEADERS += \
entity.h \
    entitymanager.h \
    database.h \
    enums/databasetype.h \
    schema.h \
    schema/sqlitequerybuilder.h \
    schema/sqliteschema.h \
    tableschema.h \
    schema/pgsqlschema.h \
    schema/mysqlschema.h \
    databasemigration.h \
    querybuilder.h \
    relation.h \
    entityinstancefactory.h \
    cache.h \
    entityhelper.h \
    logger.h \
    query.h \
    join.h \
    queryinterpreter.h \
    expression.h \
    orderby.h \
    validators/validator.h \
    validators/param.h \
    validators/errormsg.h \
    validators/defaultvalidator.h \
    validators/validatorfactory.h \
    validators/validatorrule.h \
    validators/requiredvalidator.h \
    validators/numbervalidator.h \
    validators/urlvalidator.h \
    validators/comparevalidator.h \
    validators/datevalidator.h \
    validators/emailvalidator.h \
    validators/existvalidator.h \
    validators/filevalidator.h \
    validators/imagevalidator.h \
    validators/uniquevalidator.h \
    validators/patternvalidator.h \
    validators/lengthvalidator.h \
    schema/mysqlquerybuilder.h \
    entityinspector.h \
    sqlitebackupprocessor.h \
    attribute.h \
    attributeresolver.h

SOURCES += \
entity.cpp \
    entitymanager.cpp \
    database.cpp \
    schema.cpp \
    schema/sqliteschema.cpp \
    tableschema.cpp \
    schema/pgsqlschema.cpp \
    schema/mysqlschema.cpp \
    databasemigration.cpp \
    querybuilder.cpp \
    schema/sqlitequerybuilder.cpp \
    relation.cpp \
    entityinstancefactory.cpp \
    cache.cpp \
    entityhelper.cpp \
    logger.cpp \
    query.cpp \
    join.cpp \
    queryinterpreter.cpp \
    expression.cpp \
    orderby.cpp \
    validators/validator.cpp \
    validators/param.cpp \
    validators/errormsg.cpp \
    validators/defaultvalidator.cpp \
    validators/validatorfactory.cpp \
    validators/validatorrule.cpp \
    validators/requiredvalidator.cpp \
    validators/numbervalidator.cpp \
    validators/urlvalidator.cpp \
    validators/comparevalidator.cpp \
    validators/datevalidator.cpp \
    validators/emailvalidator.cpp \
    validators/existvalidator.cpp \
    validators/filevalidator.cpp \
    validators/imagevalidator.cpp \
    validators/uniquevalidator.cpp \
    validators/patternvalidator.cpp \
    validators/lengthvalidator.cpp \
    schema/mysqlquerybuilder.cpp \
    entityinspector.cpp \
    sqlitebackupprocessor.cpp \
    attribute.cpp \
    attributeresolver.cpp

win32:!system-sqlite:!contains(LIBS, .*sqlite3.*) {
    include($$[QT_INSTALL_PREFIX]/../Src/qtbase/src/3rdparty/sqlite.pri)
} else {
    LIBS += -lsqlite3
}

CONFIG += c++14
CONFIG += create_prl
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wunreachable-code
headers.path = $$PREFIX/include/cuteEntityManager
headers.files = $$HEADERS
target.path = $$PREFIX/$$LIBDIR
INSTALLS += target headers

CONFIG(debug, debug|release) {
    DESTDIR = $$EM_DEBUG_PATH
} else {
    DESTDIR = $$EM_RELEASE_PATH
}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
