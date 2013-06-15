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

#ifndef COVARIANCEMATRIXEDITOR_H
#define COVARIANCEMATRIXEDITOR_H

#include <QWidget>
#include <QModelIndex>
#include <gnu_gama/local/observation.h>

namespace Ui {
class CovarianceMatrixEditor;
}

class CovarianceMatrixEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit CovarianceMatrixEditor(GNU_gama::local::CovMat& cov,
                                    QWidget *parent = 0);
    ~CovarianceMatrixEditor();
    
private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_tableWidget_itemSelectionChanged();
    void on_tableWidget_cellChanged(int row, int column);

    void lineEditingFinished();     // renamed from on_lineEd* to supress warnings
    void lineEditRowColumn_editingFinished();

    void on_lineEditBandWidth_editingFinished();

private:
    Ui::CovarianceMatrixEditor *ui;

    GNU_gama::local::CovMat& covmat;
    int matrixTable;
    enum {showBand, showFull};

    QBrush defaultBackground;

    void refresh();
    void clearEdits();
};

#endif // COVARIANCEMATRIXEDITOR_H
