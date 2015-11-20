lessThan(QT_MAJOR_VERSION, 5): error("requires Qt 5 or later")

TEMPLATE = subdirs
CONFIG  += ordered
SUBDIRS  = gama-q2

debug {
    SUBDIRS += gama-q2-plugins/dbdemoplugin
}
