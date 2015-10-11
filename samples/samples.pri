include(../EntityManager.pri)

QT       += core
QT       += sql
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra
INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Debug/src/ -lCuteEntityManager
else:unix:!macx:CONFIG(release, release|debug): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Release/src/ -lCuteEntityManager

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Release/release/src/ -lCuteEntityManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Debug/debug/src/ -lCuteEntityManager

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

