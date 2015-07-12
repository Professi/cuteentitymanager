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
    models/person.h \
    models/group.h \
    models/pupil.h \
    models/address.h \
    models/contact.h \
    models/faker/createfakemodeldata.h \
    models/enums.h \

SOURCES += \
    main.cpp \
    models/person.cpp \
    models/group.cpp \
    models/pupil.cpp \
    models/address.cpp \
    models/contact.cpp \
    models/faker/createfakemodeldata.cpp

unix:!macx: LIBS += -L$$PWD/../../../build-EntityManager-Desktop-Debug -lCuteEntityManager
unix:INCLUDEPATH += $$PWD/../../src
unix:DEPENDPATH += $$PWD/../../src
CONFIG += c++14

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop_Qt_5_4_1_MinGW_32bit-Debug/release/ -lCuteEntityManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-EntityManager-Desktop_Qt_5_4_1_MinGW_32bit-Debug/debug/ -lCuteEntityManager

win32:INCLUDEPATH += $$PWD/../../build-EntityManager-Desktop_Qt_5_4_1_MinGW_32bit-Debug/debug
win32:DEPENDPATH += $$PWD/../../build-EntityManager-Desktop_Qt_5_4_1_MinGW_32bit-Debug/debug
