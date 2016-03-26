#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T10:32:24
#
#-------------------------------------------------

QT       -= core gui

TARGET = gama
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

DEFINES   += GNU_gama_expat_1_1
DEFINES   += VERSION=\\\"configure.ac\\\"

LIBGAMASRC = ../gama-q2/lib/gama
include(gama.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    gama.pri
