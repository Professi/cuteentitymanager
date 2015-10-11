#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T15:03:24
#
#-------------------------------------------------

QT       += core
QT       += sql

QT       -= gui

#TARGET = EntityManager
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    address.h \
    person.h

SOURCES += \
    main.cpp \
    address.cpp \
    person.cpp

unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build-EntityManager-Desktop-Debug -lCuteEntityManager
else:unix:!macx:CONFIG(release, release|debug): LIBS += -L$$PWD/../../../build-EntityManager-Desktop-Release/ -lCuteEntityManager
unix:INCLUDEPATH += $$PWD/../../src
unix:DEPENDPATH += $$PWD/../../src
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build-EntityManager-Desktop-Release/release/ -lCuteEntityManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build-EntityManager-Desktop-Debug/debug/ -lCuteEntityManager

win32:INCLUDEPATH += $$PWD/../../../build-EntityManager-Desktop-Debug/debug
win32:DEPENDPATH += $$PWD/../../../build-EntityManager-Desktop-Debug/debug

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

unix {
QMAKE_CXXFLAGS += -Wall -Wextra -Wmaybe-uninitialized -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wunsafe-loop-optimizations -pedantic -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wunreachable-code -O -Winit-self
}

win32-g++ {
    CONFIG += c++11
    QMAKE_CXXFLAGS += -std=c++11 -Wall
}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
