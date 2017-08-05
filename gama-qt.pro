lessThan(QT_MAJOR_VERSION, 5): error("requires Qt 5 or later")

TEMPLATE = subdirs

# https://wiki.qt.io/Undocumented_QMake (5. SUBDIRS projects)
lib_gama.subdir = gama

SUBDIRS  = gama-q2 \      # Qt widgets application
           gama-local \   # C++ command line tool
           lib_gama       # C++ static library

gama-q2.depends = lib_gama
gama-local.depends = lib_gama

debug {
    adjustmentdemoplugin.subdir  = gama-q2-plugins/adjustmentdemoplugin
    adjustmentdemoplugin.depends = lib_gama
    SUBDIRS += adjustmentdemoplugin

    dbdemoplugin.subdir  = gama-q2-plugins/dbdemoplugin
    dbdemoplugin.depends = lib_gama
    SUBDIRS += dbdemoplugin
}
