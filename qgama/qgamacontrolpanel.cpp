/*  Qt based GUI for GNU Gama -- adjustment of geodetic networks
    Copyright (C) 2014, 2015, 2020  Ales Cepek <cepek@gnu.org>

    This file is a part of GNU Gama.

    GNU Gama is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GNU Gama is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <utility>

#include "qgamacontrolpanel.h"

#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QStatusBar>
#include <QFontDialog>
#include <QDebug>

#include "constants.h"
#include "dbconnection.h"
#include "dbfunctions.h"
#include "importconfigurationfile.h"
#include "importkrummnetworkfile.h"
#include "networkadjustmentpanel.h"
#include "qgamainterfaces.h"
#include "selectadjresultslanguage.h"
#include "qgamahelp.h"

#include <gnu_gama/local/localnetwork2sql.h>
#include <gnu_gama/version.h>
#include <gnu_gama/local/language.h>
#include <sstream>

namespace
{
    QGamaControlPanel* controlPanel;

    // Solution after software.rtcm-ntrip.org by Leos Mervart (GPL) 2013
    template<typename Interface>
    struct PluginAction : public QAction {
        Interface* interface_;

        PluginAction(QObject* parent, Interface* intface)
            : QAction(intface->getName(), parent), interface_(intface)
        {
        }
    };

}

void ShowMessage(QString message)
{
    controlPanel->statusBar()->showMessage(message);
}


QGamaControlPanel::QGamaControlPanel(QWidget *parent) :
    QMainWindow(parent),
    init_language_list(true)
{
    controlPanel = this;

    init_schema_lists();

    // setting implicit adjustment results language
    set_adjustment_results_language();

    setWindowTitle(QGama::name);
    load_plugins();
    build_menus();
    setMinimumSize(400, 150);
}

QGamaControlPanel::~QGamaControlPanel()
{
    // save options into database
    QSqlDatabase db = QSqlDatabase::database(QGama::connection_implicit_db);
    if (db.isOpen())
    {
        QSqlQuery q(db);
        q.exec("DELETE FROM gnu_gama_local_options "
               "WHERE opt_key='AdjResultsLanguage'");
        q.exec("INSERT INTO gnu_gama_local_options (opt_key, opt_val) "
               "VALUES ('AdjResultsLanguage','" + QGama::currentLanguage + "')");
    }
}

void QGamaControlPanel::on_action_Exit_triggered()
{
    /* emit */ adjustmentPanel(false);
    close();
}

void QGamaControlPanel::init_schema_lists()
{
    QStringList& schema = QGama::gama_local_schema;
    QStringList& tables = QGama::gama_local_schema_table_names;

    QFile rfile(":/lib/gama-local-schema.sql");
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
                    Qt::SkipEmptyParts, Qt::CaseInsensitive)[2];
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

void QGamaControlPanel::build_menus()
{
    QMenu* menuDb = new QMenu(tr("&Database"), this);

    actionDbConnect = menuDb->addAction(tr("&Connect to Database"));
    connect(actionDbConnect, SIGNAL(triggered()),
            SLOT(on_action_Connect_to_database_triggered()));

    if (actionDbConnect->isVisible()) menuDb->addSeparator();

    actionImportConf = menuDb->addAction(tr("&Import Configuration File"));
    connect(actionImportConf, SIGNAL(triggered()),
            SLOT(on_action_Import_configuration_file_triggered()));
    actionImportConf = menuDb->addAction(tr("Import &Krumm Network File"));
    connect(actionImportConf, SIGNAL(triggered()),
            SLOT(on_action_Import_krumm_network_file_triggered()));
    actionEmptyConf = menuDb->addAction(tr("&New Empty Configuration"));
    connect(actionEmptyConf, SIGNAL(triggered()),
            SLOT(on_action_New_empty_configuration_triggered()));
    actionImportExamples = menuDb->addAction(tr("Import &Examples"));
    connect(actionImportExamples, &QAction::triggered,
            this, &QGamaControlPanel::import_examples);

    menuDb->addSeparator();

    actionDbDropSchema = menuDb->addAction(tr("Drop Schema &Tables"));

    connect(actionDbDropSchema, SIGNAL(triggered()),
            SLOT(on_action_Drop_schema_Tables_triggered()));
    actionDbDeleteData = menuDb->addAction(tr("Delete all Data from the Schema"));
    connect(actionDbDeleteData, SIGNAL(triggered()),
            SLOT(on_action_Delete_all_Data_from_the_Schema_triggered()));
    actionDbDeleteConfiguration = menuDb->addAction(tr("Delete Network Configuration"));
    connect(actionDbDeleteConfiguration, SIGNAL(triggered()),
            SLOT(on_action_Delete_Network_Configuration_triggered()));

    menuDb->addSeparator();

    if (!mapDbPlugins.empty())
    {
        menuDb->addSeparator();
        for (QMap<QString, DbInterface*>::iterator
             i=mapDbPlugins.begin(), e=mapDbPlugins.end(); i!=e; ++i)
        {
            PluginAction<DbInterface>* action = new PluginAction<DbInterface>(this, *i);
            menuDb->addAction(action);
            connect(action, SIGNAL(triggered()), SLOT(dbSlot()));
        }
    }

    menuDb->addSeparator();

    actionDbExit = menuDb->addAction(tr("E&xit"));
    connect(actionDbExit, SIGNAL(triggered()),
            SLOT(on_action_Exit_triggered()));

    // ****** end of database menu


    QMenu* menuAdj = new QMenu(tr("&Adjustment"), this);
    actionAdjAdjustment = menuAdj->addAction(tr("&Network Adjustment"));
    actionAdjAdjustment->setDisabled(true);
    connect (actionAdjAdjustment, SIGNAL(triggered()),
             SLOT(on_action_Network_adjustment_triggered()));

    // ****** end of adjustment menu


    QMenu* menuTools = new QMenu(tr("&Tools"), this);
    actionAdjResultsLanguage = menuTools->addAction(tr("Adjustment results &language"));
    connect(actionAdjResultsLanguage, SIGNAL(triggered()),
            SLOT(on_action_Adjustment_results_language()));
    actionApplicationFont = menuTools->addAction(tr("Application Font"));
    connect(actionApplicationFont, SIGNAL(triggered()),
            SLOT(on_action_Application_Font()));

    // ****** end of tools menu


    QMenu* menuHelp = new QMenu(tr("&Help"), this);
    actionQGamaHelp = menuHelp->addAction(tr("Qgama &help"));
    connect(actionQGamaHelp, &QAction::triggered,
            [](){QGamaHelp::get()->show();});
    menuHelp->addSeparator();
    actionAboutQGama = menuHelp->addAction(tr("&About Qgama"));
    connect(actionAboutQGama, SIGNAL(triggered()),
            SLOT(on_action_About_qgama_triggered()));
    actionAboutQt = menuHelp->addAction(tr("About &Qt"));
    connect(actionAboutQt, SIGNAL(triggered()),
            SLOT(on_action_About_qt_triggered()));

    // ****** end of help menu


    disable_input_data(false);
    actionImportExamples->setEnabled(true);
    actionImportConf->setEnabled(true);
    actionEmptyConf->setEnabled(true);

    menuBar()->addMenu(menuDb);
    menuBar()->addMenu(menuAdj);
    menuBar()->addMenu(menuTools);
    menuBar()->addMenu(menuHelp);
}

void QGamaControlPanel::dbSlot()
{
    if (PluginAction<DbInterface>* plugin_action =
        dynamic_cast<PluginAction<DbInterface>*>(sender()))
    {
        if (QWidget* widget = plugin_action->interface_->create())
        {
            localPluginsList.append(widget);
            widget->show();
        }
    }
}

void QGamaControlPanel::closeEvent(QCloseEvent * event)
{
    QMessageBox confirm;
    confirm.setText(tr("Do you really want to exit the program?"));
    confirm.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
    if (NetworkAdjustmentPanel::allNetworkAdjustmentPanelsList.size() > 0)
    {
        confirm.addButton(QMessageBox::YesAll);
    }
    confirm.setDefaultButton  (QMessageBox::Cancel);
    int dialogCode  = confirm.exec();

    if (dialogCode == QMessageBox::Yes)
    {
        event->accept();
        QGamaHelp::get()->close();
        for (const auto& p : std::as_const(localPluginsList)) p->close();
    }
    else if (dialogCode == QMessageBox::YesAll)
    {
        NetworkAdjustmentPanel::closeAllNetworkAdjustmentPanels = true;
        for (int i=0; i<NetworkAdjustmentPanel::allNetworkAdjustmentPanelsList.size(); i++)
        {
            NetworkAdjustmentPanel::allNetworkAdjustmentPanelsList[i]->close();
        }

        event->accept();
        QGamaHelp::get()->close();
        for (const auto& p : std::as_const(localPluginsList)) p->close();
    }
    else
    {
        event->ignore();
    }
}

void QGamaControlPanel::on_action_Connect_to_database_triggered()
{
    DBConnection* d = new DBConnection(QGama::connection_implicit_db, this);
    connect(d, SIGNAL(input_data_open(bool)), this,
            SLOT(disable_input_data(bool)));
    d->exec();
    delete d;

    QSqlDatabase db = QSqlDatabase::database(QGama::connection_implicit_db);
    if (db.isOpen())
    {
        QSqlQuery q(db);
        q.exec("SELECT opt_key, opt_val FROM gnu_gama_local_options");
        while (q.next())
        {
            QString key = q.value(0).toString();
            QString val = q.value(1).toString();

            if (key == "AdjResultsLanguage") set_adjustment_results_language(val);
        }
    }
}

void QGamaControlPanel::disable_input_data(bool yes)
{
    actionDbConnect->setDisabled(yes);

    actionDbDropSchema->setEnabled(yes);
    actionDbDeleteData->setEnabled(yes);
    actionDbDeleteConfiguration->setEnabled(yes);

    actionImportConf->setEnabled(yes);
    actionEmptyConf->setEnabled(yes);
    actionImportExamples->setEnabled(yes);
    actionAdjAdjustment->setEnabled(yes);
    actionAdjResultsLanguage->setEnabled(yes);

    actionDbConnect->setVisible(!yes);

    if (yes) ShowMessage(tr("Connected to database"));
}

void QGamaControlPanel::on_action_Import_configuration_file_triggered()
{
    // if DB is not available, use sqlite memory database
    DBConnection db(QGama::connection_implicit_db);
    if (db.check_sqlite_memmory()) disable_input_data(true);

    ImportConfigurationFile* icf = new ImportConfigurationFile(true, nullptr);
    icf->exec();
}

void QGamaControlPanel::on_action_Import_krumm_network_file_triggered()
{
    // if DB is not available, use sqlite memory database
    DBConnection db(QGama::connection_implicit_db);
    if (db.check_sqlite_memmory()) disable_input_data(true);

    auto* icf = new ImportKrummNetworkFile(true, nullptr);
    icf->exec();
}

void QGamaControlPanel::on_action_New_empty_configuration_triggered()
{
    // if DB is not available, use sqlite memory database
    DBConnection db(QGama::connection_implicit_db);
    if (db.check_sqlite_memmory()) disable_input_data(true);

    ImportConfigurationFile* icf = new ImportConfigurationFile(false, nullptr);
    icf->exec();
}

void QGamaControlPanel::on_action_Network_adjustment_triggered()
{
    NetworkAdjustmentPanel* nap
        = new NetworkAdjustmentPanel(QGama::connection_implicit_db);

    connect(nap,  SIGNAL(networkAdjustmentPanel(bool)), this,
            SLOT(adjustmentPanel(bool)));
    connect(this, SIGNAL(gamaCloseSignal()), nap,
            SLOT(close()));
    nap->setAttribute(Qt::WA_DeleteOnClose);
    nap->exec();
}

void QGamaControlPanel::on_action_Drop_schema_Tables_triggered()
{
    DB_DropTables* dbf = new DB_DropTables(this);
    if (dbf->exec())
    {
        QSqlDatabase::removeDatabase(QGama::connection_implicit_db);
        disable_input_data(false);
    }
}

void QGamaControlPanel::on_action_Delete_all_Data_from_the_Schema_triggered()
{
    DB_DeleteAllData* dbf = new DB_DeleteAllData(this);
    dbf->exec();
}

void QGamaControlPanel::on_action_Delete_Network_Configuration_triggered()
{
    DB_DeleteNetworkConfiguration* dbf = new DB_DeleteNetworkConfiguration(this);
    dbf->exec();
}

void QGamaControlPanel::load_plugins()
{
    QDir qgamaplugins(qApp->applicationDirPath());
    qgamaplugins.cd("plugins");
    auto qdirfiles = qgamaplugins.entryList(QDir::Files);
    for (QString& fileName : qdirfiles) {
        QPluginLoader pluginLoader(qgamaplugins.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            if (DbInterface* dbinterface = qobject_cast<DbInterface*>(plugin))
            {
                mapDbPlugins[dbinterface->getName() + fileName] = dbinterface;
            }
        }
    }
}

void QGamaControlPanel::on_action_About_qgama_triggered()
{
    QMessageBox about(this);
    about.setIconPixmap(windowIcon().pixmap(iconSize().width()*2));

    about.setWindowTitle(tr("About QGama"));
    about.setTextFormat(Qt::RichText);
    about.setText(tr("<p>Adjustment of geodetic networks with database support</p>") +

                  "<p><b>" + QGama::name + "&nbsp;" + QGama::version + "</b>"
                  " Copyright (C) " + QGama::copyright + " Aleš Čepek <i>et al.</i></p>"
                  "<p>" +
                  QString(tr("Based on <a href='http://www.gnu.org/software/gama'>"
                             "GNU gama</a> version %1")
                         ).arg(GNU_gama::GNU_gama_version().c_str()) +
                  "  and Qt " + QString(qVersion()) +
                  "</p>"

                  "<p>This program is free software: you can redistribute it and/or modify "
                  "it under the terms of the GNU General Public License as published by "
                  "the Free Software Foundation, either version 3 of the License, or "
                  "(at your option) any later version.</p>"

                  "<p>This program is distributed in the hope that it will be useful, "
                  "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                  "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                  "GNU General Public License for more details.</p>"

                  "<p>You should have received a copy of the GNU General Public License "
                  " along with this program.  If not, see <a "
                  "href='http://www.gnu.org/licenses/'>http://www.gnu.org/licenses/</a>.</p>"
                  );
    about.exec();
}

void QGamaControlPanel::on_action_About_qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void QGamaControlPanel::set_adjustment_results_language(QString language)
{
    using namespace  GNU_gama::local;

    if      (cmp(language, "en")) set_gama_language(en);
    else if (cmp(language, "ca")) set_gama_language(ca);
    else if (cmp(language, "cs")) set_gama_language(cz);
    else if (cmp(language, "cz")) set_gama_language(cz);
    else if (cmp(language, "du")) set_gama_language(du);
    else if (cmp(language, "es")) set_gama_language(es);
    else if (cmp(language, "fr")) set_gama_language(fr);
    else if (cmp(language, "fi")) set_gama_language(fi);
    else if (cmp(language, "hu")) set_gama_language(hu);
    else if (cmp(language, "ru")) set_gama_language(ru);
    else if (cmp(language, "ua")) set_gama_language(ua);
    else if (cmp(language, "zh")) set_gama_language(zh);
    else
    {
        init_language_list = false;

        // redefine implicit language in Qt Linguist during localisation
        set_adjustment_results_language(tr("en"));
    }
    init_language_list = false;
}

void QGamaControlPanel::on_action_Application_Font()
{
  bool ok {false};
  QFont font = QFontDialog::getFont(&ok, this);
  if (ok)
    {
       QApplication::setFont(font);
       QSettings settings;
       settings.setValue("qgama-font", QApplication::font().toString());
    }
}

bool QGamaControlPanel::cmp(QString s, QString c)
{
    if (init_language_list) QGama::languages.push_back(c);

    if (s != c) return false;

    QGama::currentLanguage = c;
    return true;
}

void QGamaControlPanel::on_action_Adjustment_results_language()
{
    SelectAdjResultsLanguage dialog(this);
    dialog.exec();
}

void QGamaControlPanel::adjustmentPanel(bool newPanel)
{
    static int count;
    if (newPanel) count++;
    else          count--;

    actionDbDropSchema->setDisabled(count > 0);
}

void QGamaControlPanel::import_examples()
{
    // if DB is not available, use sqlite memory database
    DBConnection db(QGama::connection_implicit_db);
    if (db.check_sqlite_memmory()) disable_input_data(true);

    QString exdir { ":/examples/" };
    int count {0};

    QDir examples (exdir);
    auto qdirfiles = examples.entryList(QDir::Files);
    for (QString& fileName : qdirfiles) {

        count++;
        //QString confName = fileName.left(10);
        QString confName;
        for (auto c : fileName) {
            if (c == '.') break;
            confName += c;
        }
        QFile file(exdir + fileName);
        file.open(QIODevice::ReadOnly);

        std::istringstream xml { file.readAll().toStdString() };

        GNU_gama::local::LocalNetwork lnet;
        GNU_gama::local::LocalNetwork2sql imp(lnet);
        imp.readGkf(xml);

        std::stringstream sql;
        imp.write(sql, confName.toStdString());

        QSqlDatabase db = QSqlDatabase::database(QGama::connection_implicit_db);
        QSqlQuery query(db);

        db.transaction();

        std::string text;
        while (std::getline(sql, text))
        {
            // skip empty lines from imp.write(sql, confName.toStdString());
            if (text.length() == 0) continue;

            while (sql && text.back() != ';') text += char(sql.get());
            if (text.back() != ';') break;

            // avoid nested transactions
            if (text.find("begin;" ) != std::string::npos) continue;
            if (text.find("commit;") != std::string::npos) continue;

            query.exec(text.c_str());
            if (query.lastError().isValid())
            {
                QMessageBox::critical(this, tr("Database error"),
                                      query.lastError().databaseText() + "\n" + text.c_str());
                db.rollback();
                close();
                return;
            }
        }

        db.commit();
    }

    /*
    QMessageBox msgBox;
    msgBox.setText(tr("All %1 examples imported into the database").arg(count));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(tr("Import Examples"));
    msgBox.button(QMessageBox::Ok);

    QTimer::singleShot(2000, &msgBox, SLOT(close()));
    msgBox.exec();
    */
    controlPanel->statusBar()->showMessage(tr("All %1 examples imported").arg(count), 0);
}
