include(../EntityManager.pri)

QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

QT += testlib
CONFIG -= app_bundle
CONFIG += testcase
INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Debug -lCuteEntityManager
else:unix:!macx:CONFIG(release, release|debug): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Release/ -lCuteEntityManager

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Release/release/ -lCuteEntityManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop-Debug/debug/ -lCuteEntityManager
