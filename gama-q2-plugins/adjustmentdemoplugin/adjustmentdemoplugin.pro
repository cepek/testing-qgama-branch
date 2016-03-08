QT       += core gui sql widgets
TEMPLATE     = lib
CONFIG      += plugin
INCLUDEPATH +=  ../../gama-q2
INCLUDEPATH +=  ../../gama-q2/lib/gama/lib
TARGET       = $$qtLibraryTarget(adjustmentdemoplugin)

SOURCES += \
    adjustmentdemoplugin.cpp

HEADERS += \
    adjustmentdemoplugin.h

win32 {
     CONFIG(debug, release|debug):DESTDIR = ../../gama-q2/debug/plugins
     CONFIG(release, release|debug):DESTDIR = ../../gama-q2/release/plugins
 } else {
     DESTDIR = ../../gama-q2/plugins
 }

CONFIG += c++11
