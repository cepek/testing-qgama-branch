/*
  GNU Gama Qt based GUI
  Copyright (C) 2013 Ales Cepek <cepek@gnu.org>

  This file is part of GNU Gama.

  GNU Gama is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  GNU Gama is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GNU Gama.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "selectconfiguration.h"
#include "ui_selectconfiguration.h"
#include "constants.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCompleter>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

SelectConfiguration::SelectConfiguration(QString connectionName, bool tabsDocks,
                                         bool newConfName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectConfiguration), connection_name(connectionName),
    tabDockRadioButtons(tabsDocks),
    enableNewConfigurationName(newConfName),
    tabbedWidgets(true)
{
    qDebug() << "***  SelectConfiguration" << __FILE__ << __LINE__;
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("Select Configuration Name"));

    // Ok button is disabled until a valid configurations is selected
    QPushButton *okButton=ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);

    if (!tabDockRadioButtons)
    {
        ui->radioButton_tabs->hide();
        ui->radioButton_dock->hide();
        this->adjustSize();
    }
}

SelectConfiguration::~SelectConfiguration()
{
    delete ui;
}

void SelectConfiguration::select()
{
    QStringList confs;
    {
        QSqlDatabase db = QSqlDatabase::database(connection_name);
        ui->label_DatabaseName->setText(db.databaseName());

        ui->tableWidget_ExistingConfigurationNames->setColumnCount(1);
        QHeaderView* hv = new QHeaderView(Qt::Horizontal, ui->tableWidget_ExistingConfigurationNames);
        hv->setStretchLastSection(true);
        hv->setVisible(false);
        ui->tableWidget_ExistingConfigurationNames->setHorizontalHeader(hv);

        QSqlQuery query(db);
        query.exec("SELECT conf_name FROM gnu_gama_local_configurations "
                   "ORDER BY conf_name DESC");
        bool empty = true;
        while (query.next())
        {
            ui->tableWidget_ExistingConfigurationNames->insertRow(0);
            QString conf = query.value(0).toString();
            QTableWidgetItem* item = new QTableWidgetItem(conf);
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);  // the table must be readonly

            ui->tableWidget_ExistingConfigurationNames->setItem(0,0,item);

            confs << query.value(0).toString();
            empty = false;
        }

        if (empty)
        {
            QMessageBox::warning(this, tr(" Database %1").arg(db.databaseName()),
                                 tr("There are no configuration names in the database"));
            close();
            return;
        }
    }

    QCompleter *completer = new QCompleter(confs, this);
    completer->setCaseSensitivity(Qt::CaseSensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    ui->lineEdit_ConfigurationName->setCompleter(completer);

    show();
}

void SelectConfiguration::on_lineEdit_ConfigurationName_textChanged(const QString &arg1)
{
    const QRegExp whitespaces("\\s");
    ui->lineEdit_ConfigurationName->setText(QString(arg1).remove(whitespaces));

    bool found  = false;
    int  row  = 0;
    int  rows = ui->tableWidget_ExistingConfigurationNames->rowCount();
    for (int i=rows-1; i>=0; i--)
    {
        QString item = ui->tableWidget_ExistingConfigurationNames->item(i, 0)->text();
        if (item.startsWith(arg1)) row = i;
        if (item == arg1)
        {
            found = true;
            break;
        }
    }

    ui->tableWidget_ExistingConfigurationNames->selectRow(row);
    QPushButton *okButton=ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(found || enableNewConfigurationName);
}

void SelectConfiguration::on_tableWidget_ExistingConfigurationNames_cellClicked(int row, int column)
{
    QString txt = ui->tableWidget_ExistingConfigurationNames->item(row,column)->text();
    ui->lineEdit_ConfigurationName->setText(txt);
}

void SelectConfiguration::on_buttonBox_accepted()
{
    emit selectConfiguration(ui->lineEdit_ConfigurationName->text(), tabbedWidgets);
    close();
}

void SelectConfiguration::on_buttonBox_rejected()
{
    emit selectConfiguration(QString());
    close();
}

void SelectConfiguration::on_radioButton_tabs_toggled(bool /*checked*/)
{
    tabbedWidgets = ui->radioButton_tabs->isChecked();
}
