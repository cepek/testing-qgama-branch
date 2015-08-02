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

#include "dbconnectdialog.h"
#include "ui_dbconnectdialog.h"
#include "constants.h"

#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include <QDebug>

DBConnectDialog::DBConnectDialog(QString connectionName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBConnectDialog),
    connection_name(connectionName)
{
    qDebug() << "***  DBConnectDialog" << __FILE__ << __LINE__;
    ui->setupUi(this);

    setWindowTitle(tr("DB Connection"));

    const QStringList drivers = QSqlDatabase::drivers();
    ui->comboBox_Driver ->addItems(drivers);
    ui->comboBox_Driver2->addItems(drivers);

    connect(ui->comboBox_Driver,  SIGNAL(currentIndexChanged(int)), ui->comboBox_Driver2, SLOT(setCurrentIndex(int)));
    connect(ui->comboBox_Driver2, SIGNAL(currentIndexChanged(int)), ui->comboBox_Driver,  SLOT(setCurrentIndex(int)));
    connect(ui->comboBox_Driver,  SIGNAL(currentIndexChanged(int)), this, SLOT(switchStackedWidgets()));

    switchStackedWidgets();
}

DBConnectDialog::~DBConnectDialog()
{
    delete ui;
}

void DBConnectDialog::switchStackedWidgets()
{
    if (ui->comboBox_Driver->currentText() == "QSQLITE") {
        ui->stackedWidget->setCurrentIndex(1);
        ui->buttonBox->button(QDialogButtonBox::Help)->show();
    }
    else {
        ui->stackedWidget->setCurrentIndex(0);
        ui->buttonBox->button(QDialogButtonBox::Help)->hide();
    }
}

void DBConnectDialog::on_pushButton_OpenFileDialog_clicked()
{
    QFileDialog fileDialog(0,trUtf8("Opening Sqlite Database File"));
    fileDialog.setFileMode(QFileDialog::AnyFile);     // a single file only
    fileDialog.setDefaultSuffix("db");

    if (ui->checkBox_CreateNewDbFile->isChecked())
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    else
        fileDialog.setAcceptMode(QFileDialog::AcceptOpen);

    QStringList filters;
    filters << "Sqlite DB (*.db)"
            << "All files (*.*)";
    fileDialog.setNameFilters(filters);
    fileDialog.setViewMode(QFileDialog::Detail);

    if (!fileDialog.exec()) return;

    ui->lineEdit_DatabaseFile->setText( fileDialog.selectedFiles()[0] );
    on_buttonBox_accepted();
    hide();
}

void DBConnectDialog::create_missing_tables(QSqlDatabase& db)
{
    QSqlQuery query(db);

    db.transaction();
    for (QStringList::const_iterator
            i = GamaQ2::gama_local_schema.begin(),
            e = GamaQ2::gama_local_schema.end();   i!=e; ++i)
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

void DBConnectDialog::on_buttonBox_rejected()
{
    emit input_data_open(false);
}

void DBConnectDialog::on_buttonBox_accepted()
{
    QString driver = ui->comboBox_Driver->currentText();
    QString database_name = ui->lineEdit_DatabaseName->text();
    if (driver == "QSQLITE") database_name = ui->lineEdit_DatabaseFile->text();

    QSqlDatabase::removeDatabase(connection_name);
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, connection_name);
    db.setHostName    (ui->lineEdit_Hostname->text().simplified());
    db.setDatabaseName(database_name);
    db.setUserName    (ui->lineEdit_Username->text().simplified());
    db.setPassword    (ui->lineEdit_Password->text().simplified());
    if (!ui->lineEdit_Port->text().simplified().isEmpty())
    {
        db.setPort(ui->lineEdit_Port->text().toInt());
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
        for (QStringList::const_iterator i=GamaQ2::gama_local_schema_table_names.begin(),
                                         e=GamaQ2::gama_local_schema_table_names.end(); i!=e; ++i)
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
    else if (missing > 0 && missing < GamaQ2::gama_local_schema_table_names.size())
    {
        QMessageBox::critical(this, tr("Bad Database Schema Tables"),
                                    tr("One or more (but not all) of the Gnu Gama schema tables "
                                       "are missing in the database.\n\n"
                                       "Missing tables: %1").arg(missing_tables));
        db.close();

        emit input_data_open(false);
        on_buttonBox_rejected();
        return;
    }
    else if (missing == GamaQ2::gama_local_schema_table_names.size())
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
            on_buttonBox_rejected();
            return;
        }

        create_missing_tables(db);
    }

    emit input_data_open(true);
}

void DBConnectDialog::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, tr("SQLite In-Memory Database"),
       tr("You can use SQLite database with special filename :memory: "
          "to exist purely in memory. "
          "No information is implicitly stored at the disk "
          "after exiting the program."));
}
