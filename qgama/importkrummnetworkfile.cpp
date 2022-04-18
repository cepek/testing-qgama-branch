/*  Qt based GUI for GNU Gama -- adjustment of geodetic networks
    Copyright (C) 2022  Ales Cepek <cepek@gnu.org>

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

#include "importkrummnetworkfile.h"
#include "dbconnection.h"
#include "constants.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QHeaderView>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QSettings>
#include <QDebug>


// headers from gama-local-xml2sql.cpp
#include <gnu_gama/local/localnetwork2sql.h>
#include <gnu_gama/local/network.h>
#include <gnu_gama/exception.h>
#include <gnu_gama/xml/gkfparser.h>
#include <sstream>
#include <cctype>

// headers from krum2gama-local.cpp
#include <krumm/k2gkf.h>
#include <krumm/input.h>
#include <krumm/output.h>



ImportKrummNetworkFile::ImportKrummNetworkFile(bool import, QWidget *parent) :
    import_conf_(import), QWidget(parent)
{
    if (import_conf_) setWindowTitle(tr("Import XML input data"));
    else              setWindowTitle(tr("New Empty Configuration"));
    setWindowModality(Qt::ApplicationModal);

    label_File = new QLabel;
    tableWidget_ExistingConfigurationNames = new QTableWidget;
    lineEdit_ConfigurationName = new QLineEdit;
    pushButton_Import = new QPushButton;

    QFormLayout* formLayout = new QFormLayout;
    if (import_conf_) formLayout->addRow(tr("XML input file"), label_File);
    formLayout->addRow(tr("Existing configuration names"), tableWidget_ExistingConfigurationNames);
    formLayout->addRow(tr("New configuration name"), lineEdit_ConfigurationName);

    buttons = new QDialogButtonBox(QDialogButtonBox::Cancel |
                                                     QDialogButtonBox::Reset);
    buttons->addButton(tr("Import"), QDialogButtonBox::AcceptRole);

    QVBoxLayout* vBoxLayout = new QVBoxLayout;
    vBoxLayout->addLayout(formLayout);
    vBoxLayout->addWidget(buttons);
    setLayout(vBoxLayout);

    auto clicked = [this](QAbstractButton* button){
        switch (buttons->buttonRole(button)) {
        case QDialogButtonBox::RejectRole:
            close();
            break;
        case QDialogButtonBox::AcceptRole:
            import_configuration();
            break;
        case QDialogButtonBox::ResetRole:
            lineEdit_ConfigurationName->setText(basename);
            break;
        default:
            break;
        }};
    connect(buttons, &QDialogButtonBox::clicked, clicked);

    auto changed = [this](const QString& text){on_lineEdit_ConfigurationName_textChanged(text);};
    connect(lineEdit_ConfigurationName, &QLineEdit::textChanged, changed);

    auto doubleclicked = [this](int row, int col){
        lineEdit_ConfigurationName->setText(tableWidget_ExistingConfigurationNames->item(row,col)->text());
        };
    connect(tableWidget_ExistingConfigurationNames, &QTableWidget::cellDoubleClicked, doubleclicked);
}

ImportKrummNetworkFile::~ImportKrummNetworkFile()
{
}

void ImportKrummNetworkFile::exec()
{
    DBConnection dbc(QGama::connection_implicit_db);
    dbc.check_sqlite_memmory();

    QSettings settings;
    QString importdir = settings.value(import_xmldir).toString();
    QFileDialog fileDialog(nullptr,tr("Open Krumm Network File"));
    if (!importdir.isEmpty()) fileDialog.setDirectory(importdir);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    QStringList filters;
    filters << tr("Krumm network files (*.dat)")
            << tr("Any files (*)");
    fileDialog.setNameFilters(filters);
    fileDialog.setViewMode(QFileDialog::Detail);

    if (import_conf_)
      {
        if (!fileDialog.exec()) return;

        auto selected = fileDialog.selectedFiles();
        file = selected[0];
        settings.setValue(import_xmldir,
                          fileDialog.directory().absolutePath());
      }
    show();

    configure();
}

void ImportKrummNetworkFile::configure()
{
    QSqlDatabase db = QSqlDatabase::database(QGama::connection_implicit_db);
    QSqlQuery query(db);

    {
        tableWidget_ExistingConfigurationNames->setColumnCount(1);

        QHeaderView* hv = new QHeaderView(Qt::Horizontal, tableWidget_ExistingConfigurationNames);
        tableWidget_ExistingConfigurationNames->setHorizontalHeader(hv);
        hv->setStretchLastSection(true);
        hv->setVisible(false);
        tableWidget_ExistingConfigurationNames->
                setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Existing Configuration Names")));

        query.exec("SELECT conf_name "
                   "FROM   gnu_gama_local_configurations "
                   "ORDER BY conf_name DESC ");
        while (query.next())
        {
            tableWidget_ExistingConfigurationNames->insertRow(0);

            QString conf = query.value(0).toString();
            QTableWidgetItem* item = new QTableWidgetItem(conf);
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            tableWidget_ExistingConfigurationNames->setItem(0,0,item);
        }
    }

    if (import_conf_)
      {
        QFileInfo info(file);
        basename = info.baseName();
        label_File->setText(info.fileName());
        lineEdit_ConfigurationName->setText(basename);
      }
}

void ImportKrummNetworkFile::on_lineEdit_ConfigurationName_textChanged(const QString &arg1)
{
    const QRegularExpression whitespaces("\\s");
    lineEdit_ConfigurationName->setText(QString(arg1).remove(whitespaces));

    bool found  = false;
    int  row  = 0;
    int  rows = tableWidget_ExistingConfigurationNames->rowCount();
    for (int i=rows-1; i>=0; i--)
    {
        QString item = tableWidget_ExistingConfigurationNames->item(i, 0)->text();
        if (item.startsWith(arg1)) row = i;
        if (item == arg1)
        {
            found = true;
            break;
        }
    }

    tableWidget_ExistingConfigurationNames->selectRow(row);
    pushButton_Import->setEnabled(!found);
}

void ImportKrummNetworkFile::import_configuration()
{
    if (!import_conf_)
      {
        auto conf = lineEdit_ConfigurationName->text();
        if (conf.isEmpty()) return;

        QSqlDatabase db = QSqlDatabase::database(QGama::connection_implicit_db);
        QSqlQuery query(db);

        /* copied from networkadjustmentpanel.cpp, a single record with
         * conf_id and conf_name in gnu_gama_local_configurations table
         * defines the new empty configuration
         */
        try
        {
            db.transaction();
            query.exec("select conf_name FROM gnu_gama_local_configurations "
                       " where conf_name = '" + conf + "'");

            if (!query.next()) {
                // db.transaction();
                query.exec(" insert into gnu_gama_local_configurations (conf_id, conf_name) "
                           " select new_id, '" + conf + "' from (select coalesce(max(conf_id), 0)+1 as new_id from gnu_gama_local_configurations)x");
                // db.commit();
            }

            // adj.read_configuration(query, configuration_name);
        }
        catch (...)
        {
        }
        db.commit();

        close();
        return;
      }

    std::stringstream sql;
    QString qnm = label_File->text();

    QString krummString;
    QFile inputFile(file);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        krummString = in.readAll();
        inputFile.close();
    }
    else
    {
        QMessageBox::critical(this, tr("Critical Error on Opening File"), qnm);
        close();
        return;
    }

    bool repeat {false};
    do try {             // do try ... while (repeat)
        repeat = false;

        std::istringstream istr(krummString.toUtf8().toStdString());
        std::ostringstream ostr;

        GNU_gama::local::K2gkf k2gkf(istr, ostr);
        k2gkf.run();
        if (k2gkf.dimension() == 0 || k2gkf.error())
          {
            std::string err {"Bad input data, probably not Krumm network input format"};
            throw GNU_gama::local::ParserException(err, 0, 0);
          }


        std::istringstream xml(ostr.str());

        const QString qconfname = lineEdit_ConfigurationName->text();
        GNU_gama::local::LocalNetwork lnet;
        GNU_gama::local::LocalNetwork2sql imp(lnet);
        imp.readGkf(xml);
        imp.write  (sql, qconfname.toUtf8().data());
    }
    catch (const GNU_gama::local::ParserException& v)
    {
        QDialog dialog;

        dialog.setWindowTitle(tr("Import failed"));
        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(new QLabel(tr("File: ") + file + "\n" +
                                     tr("Error at line: ") + QString::number(v.line) +
                                     tr(" : ") + v.what()));

        line = new QLabel(this);
        layout->addWidget(line);

        edit = new QPlainTextEdit(krummString, this);
        QTextCursor cursor = edit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down,QTextCursor::MoveAnchor,v.line-1);
        cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
        edit->setTextCursor(cursor);
        edit->setFocus();
        layout->addWidget(edit);

        connect(edit, SIGNAL(cursorPositionChanged()), this, SLOT(setXmlLine()));
        emit edit->cursorPositionChanged();

        QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok|
                                                         QDialogButtonBox::Cancel);
        connect(buttons, SIGNAL(accepted()), &dialog, SLOT(accept()));
        connect(buttons, SIGNAL(rejected()), &dialog, SLOT(reject()));
        layout->addWidget(buttons);

        dialog.setLayout(layout);
        int result = dialog.exec();
        if (result == QDialog::Accepted)
        {
            krummString = edit->toPlainText();
            repeat = true;
        }
        else
        {
            close();
            return;
        }
    }
    catch (const GNU_gama::local::Exception& v)
    {
        QMessageBox::warning(this, tr("Import failed"), v.what());
        close();
        return;
    }
    catch (...)
    {
        QMessageBox::warning(this, tr("Import failed"), tr("Unknown exception"));
        close();
        return;
    }
    while (repeat);   // do try ... while (repeat)

    QSqlDatabase db = QSqlDatabase::database(QGama::connection_implicit_db);
    QSqlQuery query(db);

    db.transaction();

    QString str;
    std::string text;
    while(std::getline(sql, text))
    {
        if (text == "begin;") continue;
        if (text == "commit;") continue;

        bool EndOfSQL = false;
        for (std::string::const_reverse_iterator i=text.rbegin(), e=text.rend(); i!=e; ++i)
            if (!std::isspace(*i))
            {
                if (*i == ';')
                {
                    EndOfSQL = true;
                    break;
                }
            }

        str += QString::fromUtf8(text.c_str());
        str += "\n";

        if (EndOfSQL)
        {
            query.exec(str);
            if (query.lastError().isValid())
            {
                QMessageBox::critical(this, tr("Database error"),
                                      query.lastError().databaseText() + "\n" + str);
                db.rollback();
                close();
                return;
            }
            str.clear();
        }
    }

    db.commit();
    close();
}

void ImportKrummNetworkFile::setXmlLine()
{
    QString str(tr("XML Line: %1"));
    line->setText(str.arg(edit->textCursor().blockNumber() + 1));
}
