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
INCLUDEPATH += $$PWD/../gama-lib/gama/lib

OTHER_FILES +=

RESOURCES +=

LIBS += -L$$OUT_PWD/../gama-lib/ -lgama


###win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gama-lib/release/ -lgama
###else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gama-lib/debug/ -lgama
###else:unix: LIBS += -L$$OUT_PWD/../gama-lib/ -lgama

#INCLUDEPATH += $$PWD/../gama-lib/gama/lib
#DEPENDPATH  += $$PWD/../gama-lib/gama/lib

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/release/libgama.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/debug/libgama.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/release/gama.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/debug/gama.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../gama/libgama.a
