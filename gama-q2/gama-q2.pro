#-------------------------------------------------
#
# Project gama-q2
#
#-------------------------------------------------

QT        += core gui sql svg printsupport
TARGET     = gama-q2
TEMPLATE   = app

include("../gama-qt.pri")

INCLUDEPATH += lib/gama/lib

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

GAMAQ2SRC  = .
include(gama-q2.pri)

OTHER_FILES +=

RESOURCES +=

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gama/release/ -lgama
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gama/debug/ -lgama
else:unix: LIBS += -L$$OUT_PWD/../gama/ -lgama

INCLUDEPATH += $$PWD/../gama
DEPENDPATH += $$PWD/../gama

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/release/libgama.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/debug/libgama.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/release/gama.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/debug/gama.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../gama/libgama.a
