QT       += sql

TEMPLATE     = lib
CONFIG      += plugin
INCLUDEPATH +=  ../../gama-q2
TARGET       = $$qtLibraryTarget(dbdemoplugin)

SOURCES += dbdemoplugin.cpp

HEADERS += dbdemoplugin.h

win32 {
     CONFIG(debug, release|debug):DESTDIR = ../../debug/gama-q2/plugins
     CONFIG(release, release|debug):DESTDIR = ../../release/gama-q2/plugins
 } else {
     DESTDIR = ../../gama-q2/plugins
 }
