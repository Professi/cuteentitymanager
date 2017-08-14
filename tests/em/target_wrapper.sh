#!/bin/sh
PATH=/C/Qt/5.8/mingw53_32/bin:$PATH
export PATH
QT_PLUGIN_PATH=/C/Qt/5.8/mingw53_32/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}
export QT_PLUGIN_PATH
exec "$@"
