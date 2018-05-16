lessThan(QT_MAJOR_VERSION, 5): error("requires Qt 5 or later")

TEMPLATE = subdirs

SUBDIRS  = gama-q2 \      # Qt widgets application
           gama-local \   # C++ command line tool
           gama-lib       # C++ static library

gama-q2.depends = gama-lib
gama-local.depends = gama-lib

#debug {
#    adjustmentdemoplugin.subdir  = gama-q2-plugins/adjustmentdemoplugin
#    adjustmentdemoplugin.depends = lib_gama
#    SUBDIRS += adjustmentdemoplugin

#    dbdemoplugin.subdir  = gama-q2-plugins/dbdemoplugin
#    dbdemoplugin.depends = lib_gama
#    SUBDIRS += dbdemoplugin
#}
