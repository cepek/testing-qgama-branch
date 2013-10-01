#-------------------------------------------------
#
# Project gama-q2
#
#-------------------------------------------------

QT        += core gui sql svg
TARGET     = gama-q2
TEMPLATE   = app

GAMAQ2SRC  = ../src/gama-q2
DEFINES   += GNU_gama_expat_1_1
DEFINES   += VERSION=\\\"configure.ac\\\"

LIBS        += -L.. -lgama
INCLUDEPATH += lib/gama/lib

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

include(gama-q2.pri)

