/*  Qt based GUI for GNU Gama -- adjustment of geodetic networks
    Copyright (C) 2014  Ales Cepek <cepek@gnu.org>

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

#include <algorithm>

#include "dbconnection.h"
#include "constants.h"

#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QSettings>

#include <QDebug>


DBConnection::DBConnection(QString connectionName, QWidget *parent) :
    QDialog(parent),
    connection_name(connectionName)
{
    setWindowTitle(tr("DB Connection"));

    comboBox_DB_Driver = new QComboBox;
    comboBox_DB_Sqlite = new QComboBox;
    lineEdit_DatabaseName = new QLineEdit;
    lineEdit_DatabaseFile = new QLineEdit(":memory:");
    lineEdit_Hostname = new QLineEdit;
    lineEdit_Username = new QLineEdit;
    lineEdit_Password = new QLineEdit;
    lineEdit_Port = new QLineEdit;
    pushButton_CreateNewDbFile = new QPushButton(tr("Open File Dialog"));
    checkBox_CreateNewDbFile = new QCheckBox(tr("Create a New Sqlite Database File"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                     QDialogButtonBox::Cancel |
                                     QDialogButtonBox::Help);

    QStringList drivers = QSqlDatabase::drivers();
    for (QStringList::size_type i=1; i<drivers.size(); i++)
    {
      if (drivers[i] == "QSQLITE") {
        std::swap(drivers[0], drivers[i]);
        break;
      }
    }

    comboBox_DB_Driver ->addItems(drivers);
    comboBox_DB_Sqlite->addItems(drivers);

    connect(comboBox_DB_Driver,  SIGNAL(currentIndexChanged(int)), comboBox_DB_Sqlite, SLOT(setCurrentIndex(int)));
    connect(comboBox_DB_Sqlite, SIGNAL(currentIndexChanged(int)), comboBox_DB_Driver,  SLOT(setCurrentIndex(int)));
    connect(comboBox_DB_Driver,  SIGNAL(currentIndexChanged(int)), this, SLOT(switchStackedWidgets()));

    QWidget* page_0 = new QWidget;
    QWidget* page_1 = new QWidget;
    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(page_0);
    stackedWidget->addWidget(page_1);

    QFormLayout* form_0 = new QFormLayout;
    form_0->addRow(tr("Database Driver"), comboBox_DB_Driver);
    form_0->addRow(tr("Database Name"), lineEdit_DatabaseName);
    form_0->addRow(tr("Username"), lineEdit_Username);
    form_0->addRow(tr("Password"), lineEdit_Password);
    form_0->addRow(tr("Hostname"), lineEdit_Hostname);
    form_0->addRow(tr("Port"), lineEdit_Port);
    page_0->setLayout(form_0);

    QFormLayout* form_1 = new QFormLayout;
    form_1->addRow(tr("Database driver"), comboBox_DB_Sqlite);
    form_1->addRow(tr("SQLite File"), lineEdit_DatabaseFile);
    form_1->addRow(new QLabel, new QLabel);
    form_1->addRow(new QLabel, pushButton_CreateNewDbFile);
    form_1->addRow(new QLabel, checkBox_CreateNewDbFile);
    page_1->setLayout(form_1);

    switchStackedWidgets();

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(stackedWidget);
    vbox->addWidget(buttonBox);
    setLayout(vbox);

    auto bbdialog = [this](QAbstractButton* button){
            switch (buttonBox->buttonRole(button)) {
            case QDialogButtonBox::RejectRole:
                close();
                break;
            case QDialogButtonBox::AcceptRole:
                on_buttonBoxAccepted();
                break;
            case QDialogButtonBox::HelpRole:
                on_buttonBoxHelpRequested();
                break;
            default:
                break;
            }};
    connect(buttonBox, &QDialogButtonBox::clicked, bbdialog);

    auto newdbfile = [this](){on_pushButtonOpenFileDialogClicked();};
    connect(pushButton_CreateNewDbFile, &QPushButton::pressed, newdbfile);

    connect(this, &DBConnection::input_data_open,
        [this](bool open){ if (open) close();});
}

DBConnection::~DBConnection()
{
}

void DBConnection::switchStackedWidgets()
{
    if (comboBox_DB_Driver->currentText() == "QSQLITE") {
        stackedWidget->setCurrentIndex(1);
        buttonBox->button(QDialogButtonBox::Help)->show();
    }
    else {
        stackedWidget->setCurrentIndex(0);
        buttonBox->button(QDialogButtonBox::Help)->hide();
    }
}

void DBConnection::on_pushButtonOpenFileDialogClicked()
{
    QSettings settings;
    QString dbfile = settings.value(sqlite_dbfile_).toString();
    QFileDialog fileDialog(this,tr("Opening Sqlite Database File"));
    if (!dbfile.isEmpty()) fileDialog.selectFile(dbfile);
    fileDialog.setFileMode(QFileDialog::AnyFile);     // a single file only
    fileDialog.setDefaultSuffix("db");

    if (checkBox_CreateNewDbFile->isChecked())
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    else
        fileDialog.setAcceptMode(QFileDialog::AcceptOpen);

    QStringList filters;
    filters << "Sqlite DB (*.db)"
            << "All files (*.*)";
    fileDialog.setNameFilters(filters);
    fileDialog.setViewMode(QFileDialog::Detail);

    if (!fileDialog.exec()) return;

    auto selected = fileDialog.selectedFiles();
    dbfile = selected[0];
    lineEdit_DatabaseFile->setText(dbfile);
    settings.setValue(sqlite_dbfile_, dbfile);
    on_buttonBoxAccepted();
    hide();
}

void DBConnection::create_missing_tables(QSqlDatabase& db)
{
    QSqlQuery query(db);

    db.transaction();
    for (QStringList::const_iterator
            i = QGama::gama_local_schema.cbegin(),
            e = QGama::gama_local_schema.cend();   i!=e; ++i)
    {
        query.exec(*i);
        if (query.lastError().isValid())
        {
            QMessageBox::critical(this,
                tr("Database Error"),
                tr("Critical Database error occured during the "
                   "attempt to create missing schema tables.\n\n"
                   "%1").arg(query.lastError().databaseText()));
            db.rollback();
            db.close();
            emit input_data_open(false);
            close();
            return;
        }
    }
    db.commit();
}

void DBConnection::on_buttonBoxRejected()
{
    emit input_data_open(false);
}

void DBConnection::on_buttonBoxAccepted()
{
    QString driver = comboBox_DB_Driver->currentText();
    QString database_name = lineEdit_DatabaseName->text();
    if (driver == "QSQLITE") database_name = lineEdit_DatabaseFile->text();

    QSqlDatabase::removeDatabase(connection_name);
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, connection_name);
    db.setHostName    (lineEdit_Hostname->text().simplified());
    db.setDatabaseName(database_name);
    db.setUserName    (lineEdit_Username->text().simplified());
    db.setPassword    (lineEdit_Password->text().simplified());
    if (!lineEdit_Port->text().simplified().isEmpty())
    {
        db.setPort(lineEdit_Port->text().toInt());
    }

    if (!db.open())
    {
        QMessageBox::critical(this, tr("Database Error"), db.lastError().databaseText() );
        emit input_data_open(false);
        return;
    }

    if (driver == "QSQLITE" && database_name != ":memory:")
    {
        // http://www.sqlite.org/fileformat.html
        QFile file(database_name);
        file.open(QIODevice::ReadOnly);
        QByteArray headerString = file.read(16);

        if ( headerString != QByteArray("SQLite format 3\000",16) &&
            !headerString.isEmpty())
        {
            QMessageBox::critical(this, tr("Database Error"),
                                  tr("Selected file ") + database_name +
                                  tr(" is not a SQLite database"));
            emit input_data_open(false);
            return;
        }


    }

    int missing = 0;
    QString missing_tables;
    if (database_name != ":memory:")
    {
        QStringList tables = db.tables();
        for (QStringList::const_iterator i=QGama::gama_local_schema_table_names.cbegin(),
                                         e=QGama::gama_local_schema_table_names.cend(); i!=e; ++i)
            if (!tables.contains(*i, Qt::CaseInsensitive))
            {
                missing++;
                if (!missing_tables.isEmpty()) missing_tables += ", ";
                missing_tables += *i;
            }
    }

    if (database_name == ":memory:")
    {
        create_missing_tables(db);
    }
    else if (missing > 0 && missing < QGama::gama_local_schema_table_names.size())
    {
        QMessageBox::critical(this, tr("Bad Database Schema Tables"),
                                    tr("One or more (but not all) of the Gnu Gama schema tables "
                                       "are missing in the database.\n\n"
                                       "Missing tables: %1").arg(missing_tables));
        db.close();

        emit input_data_open(false);
        on_buttonBoxRejected();
        return;
    }
    else if (missing == QGama::gama_local_schema_table_names.size())
    {
        int ret = QMessageBox::question(this, tr("No Database Schema Tables"),
                                        tr("Gnu Gama schema tables are missing in the database.\n\n"
                                           "%1\n\n"
                                           "Do you want to create them?").arg(missing_tables),
                                        QMessageBox::No, QMessageBox::Yes);
        if (ret == QMessageBox::No)
        {
            db.close();

            emit input_data_open(false);
            on_buttonBoxRejected();
            return;
        }

        create_missing_tables(db);
    }

    emit input_data_open(true);
}

void DBConnection::on_buttonBoxHelpRequested()
{
    QMessageBox::information(this, tr("SQLite In-Memory Database"),
       tr("You can use SQLite database with special filename :memory: "
          "to exist purely in memory. "
          "No information is implicitly stored at the disk "
          "after exiting the program."));
}

bool DBConnection::check_sqlite_memmory()
{
  { // if DB is open, do nothing
    QSqlDatabase tmp = QSqlDatabase::database(connection_name);
    if (tmp.isOpen()) return false;
  }

  QSqlDatabase::removeDatabase(connection_name);
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection_name);
  db.setDatabaseName(":memory:");
  db.setHostName("");
  db.setUserName("");
  db.setPassword("");
  if (!db.open())
  {
      QMessageBox::critical(this, tr("Database Error"),
                            db.lastError().databaseText() );
      emit input_data_open(false);
      return false;
  }

  create_missing_tables(db);
  emit input_data_open(true);

  return true;
}
