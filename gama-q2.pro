#-------------------------------------------------
#
# Project gama-q2
#
#-------------------------------------------------

QT        += core gui sql svg
TARGET     = gama-q2
TEMPLATE   = app

LIBGAMASRC = ./lib/gama
GAMAQ2SRC  = ./src/gama-q2
DEFINES   += GNU_gama_expat_1_1
DEFINES   += VERSION=\\\"configure.ac\\\"

include(libgama.pri)
include(gama-q2.pri)
