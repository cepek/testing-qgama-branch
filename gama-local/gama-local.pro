TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(../common.pri)

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gama-lib/release/ -lgama
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gama-lib/debug/ -lgama
else:unix: LIBS += -L$$OUT_PWD/../gama-lib/ -lgama

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/release/libgama.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/debug/libgama.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/release/gama.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gama/debug/gama.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../gama/libgama.a
