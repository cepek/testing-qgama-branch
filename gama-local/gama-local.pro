TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(../common.pri)
INCLUDEPATH += $$PWD/../gama/lib

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gama-lib/release/ -lgama
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gama-lib/debug/ -lgama
else:unix: LIBS += -L$$OUT_PWD/../gama-lib/ -lgama
