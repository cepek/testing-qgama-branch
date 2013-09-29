#include "gamaq2controlpanel.h"

#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QStatusBar>
#include <QDebug>

#include "constants.h"
#include "dbconnectdialog.h"
#include "dbfunctions.h"
#include "importconfigurationfile.h"
#include "networkadjustmentpanel.h"

namespace
{
    GamaQ2ControlPanel* controlPanel;
}

void ShowMessage(QString message)
{
    controlPanel->statusBar()->showMessage(message);
}


GamaQ2ControlPanel::GamaQ2ControlPanel(QWidget *parent) :
    QMainWindow(parent)
{
    controlPanel = this;

    init_schema_lists();
    {
        GamaQ2::name    = "gama-g2";
        GamaQ2::version = "0.0";

        QFile rfile(":/lib/gama/configure.ac");
        rfile.open(QIODevice::ReadOnly);

        QTextStream configure_ac(&rfile);
        while (!configure_ac.atEnd())
        {
            QString ac_init = configure_ac.readLine();
            if (ac_init.contains("AC_INIT"))
            {
                QString ver = ac_init.split("]")[1];
                ver = ver.split("[")[1];
                GamaQ2::gnu_gama_version = ver;
                break;
            }
        }
    }

    setWindowTitle(GamaQ2::name + "  " +
                   GamaQ2::version + " / " + GamaQ2::gnu_gama_version);
    build_menus();
    setMinimumSize(400, 150);
}

GamaQ2ControlPanel::~GamaQ2ControlPanel()
{
}

void GamaQ2ControlPanel::on_action_Exit_triggered()
{
    close();
}

void GamaQ2ControlPanel::init_schema_lists()
{
    QStringList& schema = GamaQ2::gama_local_schema;
    QStringList& tables = GamaQ2::gama_local_schema_table_names;

    QFile rfile(":/lib/gama/xml/gama-local-schema.sql");
    rfile.open(QIODevice::ReadOnly);

    QTextStream sql(&rfile);

    // skip introductory comments
    while (!sql.atEnd())
    {
        QString line = sql.readLine();
        if (line.contains("*/")) break;
    }

    // read sql commands
    QStringList tmptab;
    while (!sql.atEnd())
    {
        QString command;
        while (!sql.atEnd())
        {
            QString line = sql.readLine();
            if (line.simplified().isEmpty()) continue;

            command += line;
            command += "\n";

            // extract table name
            if (line.contains("create", Qt::CaseInsensitive) &&
                line.contains("table",  Qt::CaseInsensitive) )
            {
                // create table "table name" (
                tmptab << line.split(QString(" "),
                    QString::SkipEmptyParts, Qt::CaseInsensitive)[2];
            }

            if (line.contains(";")) break;  // end of the SQL command
        }

        if (!command.isEmpty()) schema << command;
    }

    // put all tables in the order needed for sequential dropping/deleting
    tables << "gnu_gama_local_covmat";
    tmptab.removeOne("gnu_gama_local_covmat");
    tmptab.removeOne("gnu_gama_local_clusters");
    tmptab.removeOne("gnu_gama_local_configurations");
    tables << tmptab;
    tables << "gnu_gama_local_clusters";
    tables << "gnu_gama_local_configurations";
}

void GamaQ2ControlPanel::build_menus()
{
    QMenu* menuDb = new QMenu(tr("&Database"), this);
    actionDbConnect = menuDb->addAction(tr("&Connect to Database"));
    connect(actionDbConnect, SIGNAL(triggered()), SLOT(on_action_Connect_to_database_triggered()));
    actionDbImport = menuDb->addAction(tr("&Import Configuration File"));
    connect(actionDbImport, SIGNAL(triggered()), SLOT(on_action_Import_configuration_file_triggered()));
    menuDb->addSeparator();
    actionDbDropSchema = menuDb->addAction(tr("Drop Schema &Tables"));
    connect(actionDbDropSchema, SIGNAL(triggered()), SLOT(on_action_Drop_schema_Tables_triggered()));
    actionDbDeleteData = menuDb->addAction(tr("&Delete all Data from the Schema"));
    connect(actionDbDeleteData, SIGNAL(triggered()), SLOT(on_action_Delete_all_Data_from_the_Schema_triggered()));
    actionDbDeleteConfiguration = menuDb->addAction(tr("Delete &Network Configuration"));
    connect(actionDbDeleteConfiguration, SIGNAL(triggered()), SLOT(on_action_Delete_Network_Configuration_triggered()));
    if (false)
    {
        // Db plugins
    }
    menuDb->addSeparator();
    actionDbExit = menuDb->addAction(tr("&Exit"));
    connect(actionDbExit, SIGNAL(triggered()), SLOT(on_action_Exit_triggered()));

    QMenu* menuAdj = new QMenu(tr("&Adjustment"), this);
    actionAdjAdjustment = menuAdj->addAction(tr("&Network Adjustment"));
    actionAdjAdjustment->setDisabled(true);
    connect (actionAdjAdjustment, SIGNAL(triggered()), SLOT(on_action_Network_adjustment_triggered()));

    disable_input_data(false);

    menuBar()->addMenu(menuDb);
    menuBar()->addMenu(menuAdj);
}

void GamaQ2ControlPanel::closeEvent(QCloseEvent * event)
{
    QMessageBox confirm;
    confirm.setText(tr("Do you really want to exit the program?"));
    confirm.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes | QMessageBox::YesAll);
    confirm.setDefaultButton  (QMessageBox::Cancel);
    int dialogCode  = confirm.exec();

    if (dialogCode == QMessageBox::Yes)
    {
        event->accept();
    }
    else if (dialogCode == QMessageBox::YesAll)
    {
        NetworkAdjustmentPanel::closeAllNetworkAdjustmentPanels = true;
        for (int i=0; i<NetworkAdjustmentPanel::allNetworkAdjustmentPanelsList.size(); i++)
        {
            NetworkAdjustmentPanel::allNetworkAdjustmentPanelsList[i]->close();
        }

        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void GamaQ2ControlPanel::on_action_Connect_to_database_triggered()
{
    DBConnectDialog* d = new DBConnectDialog(GamaQ2::connection_implicit_db, this);
    connect(d, SIGNAL(input_data_open(bool)), this, SLOT(disable_input_data(bool)));
    d->exec();
    delete d;
}

void GamaQ2ControlPanel::disable_input_data(bool yes)
{
    actionDbConnect->setDisabled(yes);

    actionDbImport->setEnabled(yes);
    actionAdjAdjustment->setEnabled(yes);

    if (yes) ShowMessage(tr("Connected to database"));
}

void GamaQ2ControlPanel::on_action_Import_configuration_file_triggered()
{
    ImportConfigurationFile* icf = new ImportConfigurationFile(0);
    icf->exec();
}

void GamaQ2ControlPanel::on_action_Network_adjustment_triggered()
{
    NetworkAdjustmentPanel* nap = new NetworkAdjustmentPanel(GamaQ2::connection_implicit_db);
    connect(this, SIGNAL(gamaCloseSignal()), nap, SLOT(close()));
    nap->setAttribute(Qt::WA_DeleteOnClose);
    nap->exec();
}

void GamaQ2ControlPanel::on_action_Drop_schema_Tables_triggered()
{
    DB_DropTables* dbf = new DB_DropTables(this);
    dbf->exec();
}

void GamaQ2ControlPanel::on_action_Delete_all_Data_from_the_Schema_triggered()
{
    DB_DeleteAllData* dbf = new DB_DeleteAllData(this);
    dbf->exec();
}

void GamaQ2ControlPanel::on_action_Delete_Network_Configuration_triggered()
{
    DB_DeleteNetworkConfiguration* dbf = new DB_DeleteNetworkConfiguration(this);
    dbf->exec();
}
