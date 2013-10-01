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

#ifndef DRAWSETTINGS_H
#define DRAWSETTINGS_H

#include <QWidget>

namespace Ui {
class DrawSettings;
}

namespace GNU_gama { namespace local {
    class LocalNetwork;
    class GamaLocalSVG;
}}

class DrawSettings : public QWidget
{
    Q_OBJECT
    
public:
    explicit DrawSettings(GNU_gama::local::GamaLocalSVG *lsvg, QWidget *parent = 0);
    ~DrawSettings();
    
signals:
    void redraw();

private slots:
    void on_pushButtonRedraw_clicked();

private:
    Ui::DrawSettings *ui;
    GNU_gama::local::GamaLocalSVG *svg;
};

#endif // DRAWSETTINGS_H
