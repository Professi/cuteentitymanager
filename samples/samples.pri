include(../EntityManager.pri)

QT       += core
QT       += sql
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra
INCLUDEPATH += $$EM_INCLUDE_PATH

CONFIG(release, debug|release): LIBS+= -L$$EM_RELEASE_PATH $$EM_LIB
CONFIG(debug, debug|release): LIBS+= -L$$EM_DEBUG_PATH $$EM_LIB

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

