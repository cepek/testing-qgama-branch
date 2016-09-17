TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += VERSION=\\\"1.18-qt\\\"

INCLUDEPATH += $$PWD/../gama-q2/lib/gama/lib/

SOURCES += main.cpp \
    $$PWD/../gama-q2/lib/gama/lib/gnu_gama/version.cpp

HEADERS += \
    $$PWD/../gama-q2/lib/gama/lib/gnu_gama/version.h

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
