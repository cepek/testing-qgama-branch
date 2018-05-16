#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T10:32:24
#
#-------------------------------------------------

QT       -= core gui

DEFINES += GNU_gama_expat_1_1

TARGET = gama
TEMPLATE = lib
CONFIG += staticlib

DEFINES += GNU_gama_expat_1_1
LIBGAMASRC = $$PWD/gama
include(gama.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}
