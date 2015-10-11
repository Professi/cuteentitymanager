include(../samples.pri)
TEMPLATE = app
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle

HEADERS += \
    models/person.h \
    models/group.h \
    models/pupil.h \
    models/address.h \
    models/contact.h \
    models/faker/createfakemodeldata.h

SOURCES += \
    main.cpp \
    models/person.cpp \
    models/group.cpp \
    models/pupil.cpp \
    models/address.cpp \
    models/contact.cpp \
    models/faker/createfakemodeldata.cpp
