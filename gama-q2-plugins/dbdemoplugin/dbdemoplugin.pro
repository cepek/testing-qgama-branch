QT       += core gui sql widgets
TEMPLATE     = lib
CONFIG      += plugin
INCLUDEPATH +=  ../../gama-q2
TARGET       = $$qtLibraryTarget(dbdemoplugin)

SOURCES += dbdemoplugin.cpp

HEADERS += dbdemoplugin.h

win32 {
     CONFIG(debug, release|debug):DESTDIR = ../../gama-q2/debug/plugins
     CONFIG(release, release|debug):DESTDIR = ../../gama-q2/release/plugins
 } else {
     DESTDIR = ../../gama-q2/plugins
 }
