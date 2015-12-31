include(../EntityManager.pri)

QT       += core
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra
QT += testlib
CONFIG -= app_bundle
CONFIG += testcase
INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

CONFIG(release, debug|release): LIBS+= -L$$PWD/../build/release $$EM_LIB
CONFIG(debug, debug|release): LIBS+= -L$$PWD/../build/debug $$EM_LIB
