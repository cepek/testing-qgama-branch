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

#ifndef PARAMETEREDITOR_H
#define PARAMETEREDITOR_H

#include <QWidget>
#include <gnu_gama/local/network.h>

namespace Ui {
class ParameterEditor;
}

class ParameterEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit ParameterEditor(QWidget *parent = 0);
    ~ParameterEditor();

    void connectParameters(GNU_gama::local::LocalNetwork *ln);
    void enableEdit(bool edit);

private slots:
    void on_plainTextEdit_textChanged();
    void on_lineEdit_sigma_apr_editingFinished();
    void on_lineEdit_conf_pr_editingFinished();
    void on_lineEdit_tol_abs_editingFinished();
    void on_lineEdit_epoch_editingFinished();
    void on_lineEdit_latitude_editingFinished();
    void on_comboBox_sigma_act_currentIndexChanged(const QString &arg1);
    void on_comboBox_axes_xy_currentIndexChanged(const QString &arg1);
    void on_comboBox_angles_currentIndexChanged(const QString &arg1);
    void on_comboBox_algorithm_currentIndexChanged(const QString &arg1);
    void on_comboBox_ellipsoid_currentIndexChanged(const QString &arg1);
    void on_checkBox_update_cc_stateChanged(int arg1);

    void on_comboBox_ang_units_currentIndexChanged(const QString &arg1);

signals:
    void angular_units_changed();

private:
    Ui::ParameterEditor *ui;
    GNU_gama::local::LocalNetwork *lnet;
    bool readonly;
};

#endif // PARAMETEREDITOR_H
