TEMPLATE = subdirs
CONFIG  += ordered
SUBDIRS  = libgama \
           gama-q2

debug {
    SUBDIRS += gama-q2-plugins/dbdemoplugin
}
