EM_VERSION=0.1
isEmpty(EM_LIBRARY_TYPE) {
    android {
        EM_LIBRARY_TYPE = staticlib
    } else {
        EM_LIBRARY_TYPE = shared
    }
}
MAKESPEC = $$replace(QMAKESPEC,/," ")
MAKESPEC = $$replace(MAKESPEC,"\\"," ")
for(var,$$list($$MAKESPEC)) {
MAKESPEC = $$var
}
EM_INCLUDE_PATH = $$PWD/src
EM_BUILD_PATH = $$PWD/build/
EM_DEBUG_PATH = $$PWD/build/$$MAKESPEC/$$QT_ARCH/debug
EM_RELEASE_PATH = $$PWD/build/$$MAKESPEC/$$QT_ARCH/release
EM_LIB = -lCuteEntityManager

contains(EM_LIBRARY_TYPE,staticlib) {
    DEFINES += CUTE_ENTITY_MANAGER_LIBRARY_STATIC
} else {
    win32 {
        EM_LIB = -lCuteEntityManager0
    }
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
