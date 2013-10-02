QT       += sql

TEMPLATE     = lib
CONFIG      += plugin
INCLUDEPATH +=  ../../gama-q2
TARGET       = $$qtLibraryTarget(dbdemoplugin)

DESTDIR = ..

SOURCES += dbdemoplugin.cpp

HEADERS += dbdemoplugin.h

#symbian {
#    MMP_RULES += EXPORTUNFROZEN
#    TARGET.UID3 = 0xEA7643B4
#    TARGET.CAPABILITY =
#    TARGET.EPOCALLOWDLLDATA = 1
#    addFiles.sources = dbdemo.dll
#    addFiles.path = !:/sys/bin
#    DEPLOYMENT += addFiles
#}
#
#unix:!symbian {
#    maemo5 {
#        target.path = /opt/usr/lib
#    } else {
#        target.path = /usr/lib
#    }
#    INSTALLS += target
#}
