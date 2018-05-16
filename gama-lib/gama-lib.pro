#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T10:32:24
#
#-------------------------------------------------

QT       -= core gui

TARGET = gama
TEMPLATE = lib
CONFIG += staticlib

include(../common.pri)

LIBGAMASRC = $$PWD/gama
include(gama.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}
