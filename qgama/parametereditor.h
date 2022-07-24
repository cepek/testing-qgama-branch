/*
  GNU Gama Qt based GUI
  Copyright (C) 2013, 2020 Ales Cepek <cepek@gnu.org>

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

class QCheckBox;
class QComboBox;
class QLineEdit;
class QPlainTextEdit;
class QLabel;

class ParameterEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit ParameterEditor(QWidget *parent = nullptr);
    ~ParameterEditor();

    void connectParameters(GNU_gama::local::LocalNetwork *ln);
    void enableEdit(bool edit);

private slots:
    void par_description_editingFinished();
    void par_sigma_apr_editingFinished();
    void par_conf_pr_editingFinished();
    void par_tol_abs_editingFinished();
    void par_iterations_editingFinished();
    void par_epoch_editingFinished();
    void par_latitude_editingFinished();
    void par_sigma_act_currentTextChanged(const QString &arg1);
    void par_axes_xy_currenTextChanged(const QString &arg1);
    void par_angles_currentTextChanged(const QString &arg1);
    void par_algorithm_currentTextChanged(const QString &arg1);
    void par_ellipsoid_currentTextChanged(const QString &arg1);
    void par_ang_units_currentTextChanged(const QString &arg1);
    void par_adj_covband_editingFinished();

signals:
    void angular_units_changed();

private:

    QComboBox *comboBox_sigma_act;
    QComboBox *comboBox_axes_xy;
    QComboBox *comboBox_angles;
    QComboBox *comboBox_algorithm;
    QComboBox *comboBox_ang_units;
    QComboBox *comboBox_ellipsoid;
    QLineEdit *lineEdit_sigma_apr;
    QLineEdit *lineEdit_conf_pr;
    QLineEdit *lineEdit_tol_abs;
    QLineEdit *lineEdit_epoch;
    QLineEdit *lineEdit_adj_covband;
    QLineEdit *lineEdit_latitude;
    QLineEdit *lineEdit_iterations;

    QPlainTextEdit *par_description;

    GNU_gama::local::LocalNetwork *lnet;
    bool readonly;
};

#endif // PARAMETEREDITOR_H
