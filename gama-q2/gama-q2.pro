#-------------------------------------------------
#
# Project gama-q2
#
#-------------------------------------------------

QT        += core gui sql svg
TARGET     = gama-q2
TEMPLATE   = app

DEFINES   += GNU_gama_expat_1_1
DEFINES   += VERSION=\\\"configure.ac\\\"

INCLUDEPATH += lib/gama/lib

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

GAMAQ2SRC  = .
include(gama-q2.pri)


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libgama/release/ -llibgama
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libgama/debug/ -llibgama
else:symbian: LIBS += -llibgama
else:unix: LIBS += -L$$OUT_PWD/../libgama/ -llibgama

INCLUDEPATH += $$PWD/../libgama
DEPENDPATH += $$PWD/../libgama

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libgama/release/libgama.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libgama/debug/libgama.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../libgama/liblibgama.a
