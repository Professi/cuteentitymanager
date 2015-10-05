include (EntityManager.pri)
QT       += core
QT       += sql
#if you need Image Validation you must compile with += gui
#QT       += gui
QT       -= gui

TARGET = CuteEntityManager
TEMPLATE = lib

HEADERS += \
src/entity.h \
    src/entitymanager.h \
    src/database.h \
    src/enums/databasetype.h \
    src/schema.h \
    src/schema/sqlitequerybuilder.h \
    src/schema/sqliteschema.h \
    src/tableschema.h \
    src/schema/pgsqlschema.h \
    src/schema/mysqlschema.h \
    src/databasemigration.h \
    src/querybuilder.h \
    src/relation.h \
    src/entityinstancefactory.h \
    src/cache.h \
    src/entityhelper.h \
    src/logger.h \
    src/query.h \
    src/join.h \
    src/queryinterpreter.h \
    src/expression.h \
    src/orderby.h \
    src/validators/validator.h \
    src/validators/param.h \
    src/validators/errormsg.h \
    src/validators/defaultvalidator.h \
    src/validators/validatorfactory.h \
    src/validators/validatorrule.h \
    src/validators/requiredvalidator.h \
    src/validators/numbervalidator.h \
    src/validators/urlvalidator.h \
    src/validators/comparevalidator.h \
    src/validators/datevalidator.h \
    src/validators/emailvalidator.h \
    src/validators/existvalidator.h \
    src/validators/filevalidator.h \
    src/validators/imagevalidator.h \
    src/validators/uniquevalidator.h \
    src/validators/patternvalidator.h \
    src/validators/lengthvalidator.h \
    src/schema/mysqlquerybuilder.h \
    src/entityinspector.h

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
    src/expression.cpp \
    src/orderby.cpp \
    src/validators/validator.cpp \
    src/validators/param.cpp \
    src/validators/errormsg.cpp \
    src/validators/defaultvalidator.cpp \
    src/validators/validatorfactory.cpp \
    src/validators/validatorrule.cpp \
    src/validators/requiredvalidator.cpp \
    src/validators/numbervalidator.cpp \
    src/validators/urlvalidator.cpp \
    src/validators/comparevalidator.cpp \
    src/validators/datevalidator.cpp \
    src/validators/emailvalidator.cpp \
    src/validators/existvalidator.cpp \
    src/validators/filevalidator.cpp \
    src/validators/imagevalidator.cpp \
    src/validators/uniquevalidator.cpp \
    src/validators/patternvalidator.cpp \
    src/validators/lengthvalidator.cpp \
    src/schema/mysqlquerybuilder.cpp \
    src/entityinspector.cpp
    
!win32 { # looks bad.
    HEADERS += \
    src/sqlitebackupprocessor.h
    SOURCES += \
        src/sqlitebackupprocessor.cpp
    LIBS += -lsqlite3
}
    
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra -Wunsafe-loop-optimizations -pedantic -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wunreachable-code
#headers.path = $$PREFIX/include/cuteEntityManager
#headers.files = $$HEADERS
#target.path = $$PREFIX/$$LIBDIR
#INSTALLS += target

unix {
    QMAKE_CXXFLAGS += -Wunsafe-loop-optimizations -pedantic -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wunreachable-code
    #linux-g++5 {
    #QMAKE_CXXFLAGS += -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wmaybe-uninitialized
    #}
}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

DISTFILES += \
    README.md \
    LICENSE \
    AUTHORS \
    Doxyfile
