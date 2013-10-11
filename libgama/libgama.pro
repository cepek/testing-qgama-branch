QT      -= core gui

TARGET   = libgama
TEMPLATE = lib
CONFIG  += staticlib

DEFINES   += GNU_gama_expat_1_1
DEFINES   += VERSION=\\\"configure.ac\\\"

LIBGAMASRC = ../gama-q2/lib/gama
include(libgama.pri)

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
