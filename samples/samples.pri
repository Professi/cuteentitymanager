include(../EntityManager.pri)

QT       += core
QT       += sql
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra
INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Debug/src/ $$EM_LIB
else:unix:!macx:CONFIG(release, release|debug): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Release/src/ $$EM_LIB
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Release/src/release $$EM_LIB0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Debug/src/debug $$EM_LIB

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

