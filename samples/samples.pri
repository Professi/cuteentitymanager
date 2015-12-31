include(../EntityManager.pri)

QT       += core
QT       += sql
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra
INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

CONFIG(release, debug|release): LIBS+= -L$$PWD/../build/release $$EM_LIB
CONFIG(debug, debug|release): LIBS+= -L$$PWD/../build/debug $$EM_LIB

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

