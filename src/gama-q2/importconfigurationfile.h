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

#ifndef IMPORTCONFIGURATIONFILE_H
#define IMPORTCONFIGURATIONFILE_H

#include <QWidget>

namespace Ui {
    class ImportConfigurationFile;
}

class ImportConfigurationFile : public QWidget
{
    Q_OBJECT

public:
    explicit ImportConfigurationFile(QWidget *parent = 0);
    ~ImportConfigurationFile();

    void exec();

private slots:
    void on_pushButton_Cancel_clicked();
    void on_lineEdit_ConfigurationName_textChanged(const QString &arg1);

    void on_pushButton_Import_clicked();

private:
    Ui::ImportConfigurationFile *ui;
    QString file;

    void configure();
};

#endif // IMPORTCONFIGURATIONFILE_H
