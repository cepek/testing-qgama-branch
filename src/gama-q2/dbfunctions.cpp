#include "dbfunctions.h"
#include "constants.h"
#include "selectconfiguration.h"
#include "dbconnectdialog.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DropDeleteBase::DropDeleteBase(QWidget *parent) : QWidget(parent) { needsConfName = false; }

DB_DropTables::DB_DropTables(QWidget *parent) : DropDeleteBase(parent) {}

void DB_DropTables::init()
{
    confirmWindowTitle = tr("Drop Gama Tables");
    confirmQuestion    = tr("Do you really want to remove all Gama tables from the database?");
    critical_1         = tr("Schema tables cannot be dropped from the implicitly open datatase.");
    critical_2         = tr("Database tables cannot be dropped. Database connection is not open.");
    critical_3         = tr("Database tables cannot be dropped.\n\n%1");
    query_string       = "DROP TABLE %1%2";      // table name, confName
    confName.clear();
}

DB_DeleteAllData::DB_DeleteAllData(QWidget *parent) : DropDeleteBase(parent) {}

void DB_DeleteAllData::init()
{
    confirmWindowTitle = tr("Delete Gama Tables");
    confirmQuestion    = tr("Do you really want to delete all data from Gama tables in the database?");
    critical_1         = tr("Data cannot be deleted from tables in the implicitly open datatase.");
    critical_2         = tr("Data cannot be deleted. Database connection is not open.");
    critical_3         = tr("Data cannot be deleted.\n\n%1");
    query_string       = "DELETE FROM %1%2";      // table name, confName
    confName.clear();
}

DB_DeleteNetworkConfiguration::DB_DeleteNetworkConfiguration(QWidget *parent) : DropDeleteBase(parent) {}

void DB_DeleteNetworkConfiguration::init()
{
    needsConfName      = true;
    confirmWindowTitle = tr("Delete Network Configuration");
    confirmQuestion    = tr("Do you really want to delete a network configuration in the database?");
    critical_1         = tr("Network configuration cannot be deleted in the implicitly open datatase.");
    critical_2         = tr("Network configuration cannot be deleted. Database connection is not open.");
    critical_3         = tr("Network configuration cannot be deleted.\n\n%1");
    query_string       = "DELETE FROM %1 WHERE conf_id=(SELECT conf_id "
                         "                              FROM   gnu_gama_local_configurations "
                         "                              WHERE  conf_name='%2')";  // table name, confName
    confName.clear();
}

void DB_DeleteNetworkConfiguration::getConfigurationName(QString name)
{
    confName = name;
    needsConfName = false;
    drop_or_delete_schema_tables(true);
}

// ----------------------------------------------------------------------------

void DropDeleteBase::exec()
{
    setAttribute(Qt::WA_DeleteOnClose);
    init();

    QMessageBox confirm;
    confirm.setWindowTitle(confirmWindowTitle);
    confirm.setText(confirmQuestion);
    confirm.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
    confirm.setDefaultButton  (QMessageBox::Cancel);
    int dialogCode  = confirm.exec();

    DBConnectDialog* dbc = new DBConnectDialog(GamaQ2::connection_dbf_drop_tables);
    connect(dbc, SIGNAL(input_data_open(bool)), this, SLOT(drop_or_delete_schema_tables(bool)));
    dbc->exec();
    delete dbc;

    close();
}

void DropDeleteBase::drop_or_delete_schema_tables(bool connected)
{
    if (!connected)
    {
        close();
        return;
    }

    QSqlDatabase drop = QSqlDatabase::database(GamaQ2::connection_dbf_drop_tables);
    QSqlDatabase impl = QSqlDatabase::database(GamaQ2::connection_implicit_db);

    if (drop.isOpen() && impl.isOpen() && (drop.databaseName() == impl.databaseName()))
    {
        QMessageBox::critical(this, tr("Database %1").arg(drop.databaseName()), critical_1);
        close();
        return;
    }

    if (!drop.isOpen())
    {
        QMessageBox::critical(this, tr("Database Connection Failed"), critical_2);
        close();
        return;
    }

    if (needsConfName)
    {
        qDebug() << GamaQ2::connection_dbf_drop_tables
                    << QSqlDatabase::database(GamaQ2::connection_dbf_drop_tables).isOpen();
        SelectConfiguration* sc = new SelectConfiguration(GamaQ2::connection_dbf_drop_tables, false, false, this);
        connect(sc, SIGNAL(selectConfiguration(QString)), this, SLOT(getConfigurationName(QString)));
        sc->exec();
        qDebug() << "operace neni implementovana";
        return;
    }

    QSqlQuery dq(drop);

    drop.transaction();

    QStringList tables = GamaQ2::gama_local_schema_table_names;
    for (QStringList::const_iterator i=tables.begin(), e=tables.end(); i!=e; ++i)
    {
        dq.exec(QString(query_string).arg(*i).arg(confName));
        if (dq.lastError().isValid())
        {
            QMessageBox::critical(this, tr("Database Error"),
                                  critical_3.arg(dq.lastError().databaseText()));
            drop.rollback();
            drop.close();
            close();
            return;
        }
    }

    drop.commit();
    drop.close();

    QMessageBox::information(this, confirmWindowTitle, tr("Operation succesfully completed"));
    close();
}
