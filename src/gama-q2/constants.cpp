#include "constants.h"

QString GamaQ2::name;
QString GamaQ2::version;
QString GamaQ2::gnu_gama_version;

QStringList GamaQ2::gama_local_schema;
QStringList GamaQ2::gama_local_schema_table_names;

const QString GamaQ2::connection_implicit_db     = "connection_implicit_db";
const QString GamaQ2::connection_dbf_drop_tables = "connection_dbf_drop_tables";

const QString GamaQ2::obsClusterName = "obs";
const QString GamaQ2::xyzClusterName = "xyz";
const QString GamaQ2::hdfClusterName = "hdf";
const QString GamaQ2::vecClusterName = "vec";

const QString GamaQ2::distObsName    = "dist.";
const QString GamaQ2::dirObsName     = "dir.";
const QString GamaQ2::angleObsName   = "angle";
const QString GamaQ2::hdifObsName    = "h dif";
const QString GamaQ2::xdifObsName    = "x dif";
const QString GamaQ2::ydifObsName    = "y dif";
const QString GamaQ2::zdifObsName    = "z dif";
const QString GamaQ2::xObsName       = "x";
const QString GamaQ2::yObsName       = "y";
const QString GamaQ2::zObsName       = "z";
const QString GamaQ2::slopeObsName   = "slope";
const QString GamaQ2::zangleObsName  = "zangle";

const QColor GamaQ2::colorClusterHeader     = QColor(210,210,210);
const QColor GamaQ2::colorPassiveBackground = QColor(240,240,240);   // Qt::lightGray is too dark
const QColor GamaQ2::colorOutsideCovMat     = Qt::lightGray;
const QColor GamaQ2::colorSingularCovMat    = Qt::red;
