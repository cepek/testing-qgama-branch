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

#ifndef DBCONNECTDIALOG_H
#define DBCONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class DBConnectDialog;
}

class QSqlDatabase;

class DBConnectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DBConnectDialog(QString connectionName, QWidget *parent = 0);
    ~DBConnectDialog();
    
private:
    Ui::DBConnectDialog *ui;
    QString connection_name;

    void create_missing_tables(QSqlDatabase& db);

private slots:
    void switchStackedWidgets();
    void on_pushButton_OpenFileDialog_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

signals:
    void input_data_open(bool);
};

#endif // DBCONNECTDIALOG_H
