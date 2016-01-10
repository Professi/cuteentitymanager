include(../EntityManager.pri)

QT       += core
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra
QT += testlib
CONFIG -= app_bundle
CONFIG += testcase
INCLUDEPATH += $$EM_INCLUDE_PATH

CONFIG(release, debug|release): LIBS+= -L$$EM_RELEASE_PATH $$EM_LIB
CONFIG(debug, debug|release): LIBS+= -L$$EM_DEBUG_PATH $$EM_LIB

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
