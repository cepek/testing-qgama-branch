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

#ifndef SELECTCONFIGURATION_H
#define SELECTCONFIGURATION_H

#include <QDialog>

namespace Ui {
    class SelectConfiguration;
}

class SelectConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit SelectConfiguration(QString connectionName, bool tabsDocks,
                                 bool newConfName, QWidget *parent = 0);
    ~SelectConfiguration();

    void select();

private slots:
    void on_lineEdit_ConfigurationName_textChanged(const QString &arg1);
    void on_tableWidget_ExistingConfigurationNames_cellClicked(int row, int column);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_radioButton_tabs_toggled(bool checked);

private:
    Ui::SelectConfiguration *ui;


    QString connection_name;
    QString configuration_name;
    bool    tabDockRadioButtons;
    bool    enableNewConfigurationName;
    bool    tabbedWidgets;

signals:
    void selectConfiguration(QString conf, bool useTabbedWidgets=true);
};

#endif // SELECTCONFIGURATION_H
