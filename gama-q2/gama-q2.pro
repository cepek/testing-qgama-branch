#-------------------------------------------------
#
# Project gama-q2
#
#-------------------------------------------------

QT        += core gui sql svg printsupport
TARGET     = gama-q2
TEMPLATE   = app

include(../common.pri)

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

GAMAQ2SRC  = .
include(gama-q2.pri)
INCLUDEPATH += $$PWD/../gama/lib

OTHER_FILES +=

RESOURCES +=

LIBS += -L$$OUT_PWD/../gama-lib/ -lgama

