EM_VERSION=0.1
isEmpty(EM_LIBRARY_TYPE) {
    android {
        EM_LIBRARY_TYPE = staticlib
    } else {
        EM_LIBRARY_TYPE = shared
    }
}

EM_INCLUDEPATH = $$PWD/src
EM_LIB = -lCuteEntityManager
contains(EM_LIBRARY_TYPE,staticlib) {
    DEFINES += CUTE_ENTITY_MANAGER_LIBRARY_STATIC
} else {
    DEFINES += CUTE_ENTITY_MANAGER_LIBRARY_SHARED
}

# Installation prefix and library directory
isEmpty(PREFIX) {
    contains(MEEGO_EDITION,harmattan) {
        PREFIX = /usr
    } else:unix {
        PREFIX = /usr/local
    } else {
        PREFIX = $$[QT_INSTALL_PREFIX]
    }
}
isEmpty(LIBDIR) {
    LIBDIR=lib
}
