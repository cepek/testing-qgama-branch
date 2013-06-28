#include "constants.h"

QString GamaQ2::name;
QString GamaQ2::version;
QString GamaQ2::gnu_gama_version;

QStringList GamaQ2::gama_local_schema;
QStringList GamaQ2::gama_local_schema_table_names;

const QString GamaQ2::connection_implicit_db     = "connection_implicit_db";
const QString GamaQ2::connection_dbf_drop_tables = "connection_dbf_drop_tables";

const QColor GamaQ2::colorClusterHeader     = QColor(210,210,210);
const QColor GamaQ2::colorPassiveBackground = QColor(240,240,240);   // Qt::lightGray is too dark
const QColor GamaQ2::colorOutsideCovMat     = Qt::lightGray;
