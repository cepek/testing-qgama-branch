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

#include "observationeditor.h"
#include "ui_observationeditor.h"

#include <gnu_gama/local/network.h>

ObservationEditor::ObservationEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObservationEditor),
    model(0), readonly(true)
{
    ui->setupUi(this);

    enableEdit(false);
}

ObservationEditor::~ObservationEditor()
{
    delete ui;
}

void ObservationEditor::connectObservationData(GNU_gama::local::LocalNetwork *lnet)
{
    ObservationTableModel* old = model;
    model = new ObservationTableModel(lnet, this);
    ui->tableView->setModel(model);
    delete old;

    connect(model, SIGNAL(warning(QString)), this, SIGNAL(warning(QString)));
}

void ObservationEditor::enableEdit(bool edit)
{
    readonly = !edit;
    if (edit)
    {
        // implicit behaviour is "double click for editing"
        ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    }
    else
    {
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}
