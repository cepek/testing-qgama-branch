QT      -= core gui

TARGET   = ../gama
TEMPLATE = lib
CONFIG  += staticlib

LIBGAMASRC = ./gama
DEFINES   += GNU_gama_expat_1_1
DEFINES   += VERSION=\\\"configure.ac\\\"

include(libgama.pri)

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
