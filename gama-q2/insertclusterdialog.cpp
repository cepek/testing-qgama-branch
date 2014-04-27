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

#include "insertclusterdialog.h"
#include "ui_insertclusterdialog.h"
#include "constants.h"
#include <QDebug>

InsertClusterDialog::InsertClusterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertClusterDialog)
{
    qDebug() << "***  InsertClusterDialog" << __FILE__ << __LINE__;
    ui->setupUi(this);

    ui->comboBoxClusterName->addItem(GamaQ2::obsClusterName);
    ui->comboBoxClusterName->addItem(GamaQ2::xyzClusterName);
    ui->comboBoxClusterName->addItem(GamaQ2::hdfClusterName);
    ui->comboBoxClusterName->addItem(GamaQ2::vecClusterName);

    ui->comboBoxPosition->addItem(tr("Last item in the cluster list"));
    ui->comboBoxPosition->addItem(tr("After the selected cluster"));
    ui->comboBoxPosition->addItem(tr("Before the selected cluster"));
    ui->comboBoxPosition->addItem(tr("First item in the cluster list"));
}

InsertClusterDialog::~InsertClusterDialog()
{
    delete ui;
}

QString InsertClusterDialog::clusterName() const
{
    return ui->comboBoxClusterName->currentText();
}

int InsertClusterDialog::position() const
{
    return ui->comboBoxPosition->currentIndex();
}
