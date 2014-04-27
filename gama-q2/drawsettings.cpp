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

#include "drawsettings.h"
#include "ui_drawsettings.h"

#include <gnu_gama/local/svg.h>

#include <QDebug>

DrawSettings::DrawSettings(GNU_gama::local::GamaLocalSVG *lsvg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawSettings),
    svg(lsvg)
{
    qDebug() << "***  DrawSettings" << __FILE__ << __LINE__;
    ui->setupUi(this);

    QStringList pointsymbols;
    pointsymbols << "triangle" << "circle" << "none";
    ui->comboBoxFixedSymbol      ->addItems(pointsymbols);
    ui->comboBoxConstrainedSymbol->addItems(pointsymbols);
    ui->comboBoxFreeSymbol       ->addItems(pointsymbols);

    QStringList pointfill;
    // 16 basic colors
    pointfill << "aqua"   << "black" << "blue"   << "fuchsia"
              << "gray"   << "green" << "lime"   << "maroon"
              << "navy"   << "olive" << "purple" << "red"
              << "silver" << "teal"  << "white"  << "yellow"
              << "none";
    ui->comboBoxFixedFill      ->addItems(pointfill);
    ui->comboBoxConstrainedFill->addItems(pointfill);
    ui->comboBoxFreeFill       ->addItems(pointfill);


    ui->checkBoxDrawPointSymbols->setChecked(svg->drawPointSymbols());
    ui->checkBoxDrawPointIDs    ->setChecked(svg->drawPoinsIDs());
    ui->checkBoxDrawEllipses    ->setChecked(svg->drawEllipses());
    ui->checkBoxDrawObservations->setChecked(svg->drawPoinsObservations());
    ui->checkBoxDrawAxes        ->setChecked(svg->drawAxes());

    ui->spinBoxFontSize   ->setValue(svg->fontSize());
    ui->spinBoxSymbolSize ->setValue(svg->symbolSize());
    ui->spinBoxStrokeWidth->setValue(svg->strokeWidth());

    ui->comboBoxFixedSymbol      ->setCurrentIndex(pointsymbols.indexOf(svg->fixedSymbol().c_str()));
    ui->comboBoxConstrainedSymbol->setCurrentIndex(pointsymbols.indexOf(svg->constrainedSymbol().c_str()));
    ui->comboBoxFreeSymbol       ->setCurrentIndex(pointsymbols.indexOf(svg->freeSymbol().c_str()));

    ui->comboBoxFixedFill      ->setCurrentIndex(pointfill.indexOf(svg->fixedFill().c_str()));
    ui->comboBoxConstrainedFill->setCurrentIndex(pointfill.indexOf(svg->constrainedFill().c_str()));
    ui->comboBoxFreeFill       ->setCurrentIndex(pointfill.indexOf(svg->freeFill().c_str()));
}

DrawSettings::~DrawSettings()
{
    delete ui;
}

void DrawSettings::on_pushButtonRedraw_clicked()
{
    svg->setDrawPointSymbols(ui->checkBoxDrawPointSymbols->isChecked());
    svg->setDrawPointIDs    (ui->checkBoxDrawPointIDs    ->isChecked());
    svg->setDrawEllipses    (ui->checkBoxDrawEllipses    ->isChecked());
    svg->setDrawObservations(ui->checkBoxDrawObservations->isChecked());
    svg->setDrawAxes        (ui->checkBoxDrawAxes        ->isChecked());

    svg->setFontSize   (ui->spinBoxFontSize   ->value());
    svg->setSymbolSize (ui->spinBoxSymbolSize ->value());
    svg->setStrokeWidth(ui->spinBoxStrokeWidth->value());

    svg->setFixedSymbol      (ui->comboBoxFixedSymbol      ->currentText().toStdString());
    svg->setConstrainedSymbol(ui->comboBoxConstrainedSymbol->currentText().toStdString());
    svg->setFreeSymbol       (ui->comboBoxFreeSymbol       ->currentText().toStdString());

    svg->setFixedFill      (ui->comboBoxFixedFill      ->currentText().toStdString());
    svg->setConstrainedFill(ui->comboBoxConstrainedFill->currentText().toStdString());
    svg->setFreeFill       (ui->comboBoxFreeFill       ->currentText().toStdString());

    emit redraw();
}
