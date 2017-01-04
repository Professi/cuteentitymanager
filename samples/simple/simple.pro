#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T15:03:24
#
#-------------------------------------------------
include(../samples.pri)
QT       += core
QT       += sql
QT       -= gui

#TARGET = EntityManager
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    ratingmarkincident.h \
    incident.h \
    ratingmarksystem.h \
    ratingmarkdefinition.h \
    enums.h \
    datacreation.h \
    group.h \
    person.h \
    pupil.h \
    stuff.h

SOURCES += \
    main.cpp \
    ratingmarkincident.cpp \
    incident.cpp \
    ratingmarksystem.cpp \
    ratingmarkdefinition.cpp \
    datacreation.cpp \
    group.cpp \
    person.cpp \
    pupil.cpp
