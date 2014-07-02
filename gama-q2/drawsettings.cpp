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

    //QPushButton *help = new QPushButton(tr("Help"));
    //ui->buttonBox->addButton(help, QDialogButtonBox::HelpRole);

    pointsymbols << "triangle" << "circle" << "none";
    ui->comboBoxFixedSymbol      ->addItems(pointsymbols);
    ui->comboBoxConstrainedSymbol->addItems(pointsymbols);
    ui->comboBoxFreeSymbol       ->addItems(pointsymbols);

    // 16 basic colors
    pointfill << "aqua"   << "black" << "blue"   << "fuchsia"
              << "gray"   << "green" << "lime"   << "maroon"
              << "navy"   << "olive" << "purple" << "red"
              << "silver" << "teal"  << "white"  << "yellow"
              << "none";
    ui->comboBoxFixedFill      ->addItems(pointfill);
    ui->comboBoxConstrainedFill->addItems(pointfill);
    ui->comboBoxFreeFill       ->addItems(pointfill);

    setSpinBoxDefaults(ui->doubleSpinBoxFontSize);
    setSpinBoxDefaults(ui->doubleSpinBoxSymbolSize);
    setSpinBoxDefaults(ui->doubleSpinBoxStrokeWidth);

    readSvgValues();

    // stored values for Reset function
    r_drawPointSymbols = svg->drawPointSymbols();
    r_drawPointIDs = svg->drawPointIDs();
    r_drawEllipses = svg->drawEllipses();
    r_drawObservations = svg->drawObservations();
    r_drawAxes = svg->drawAxes();

    r_fontSize = svg->fontSize();
    r_symbolSize = svg->symbolSize();
    r_strokeWidth = svg->strokeWidth();

    r_fixedSymbol = svg->fixedSymbol();
    r_constrainedSymbol = svg->constrainedSymbol();
    r_freeSymbol = svg->freeSymbol();

    r_fixedFill = svg->fixedFill();
    r_constrainedFill = svg->constrainedFill();
    r_freeFill = svg->freeFill();
}

DrawSettings::~DrawSettings()
{
    delete ui;
}

void DrawSettings::setSpinBoxDefaults(QDoubleSpinBox *spinBox)
{
    const double minv = 0.0001;
    const double maxv = 1000 - minv;

    spinBox->setDecimals(4);
    spinBox->setMaximum(maxv);
    spinBox->setMinimum(minv);
    spinBox->setSingleStep(0.1);
    spinBox->adjustSize();

    spinBox->setValue(minv);
}

void DrawSettings::readSvgValues()
{
    ui->checkBoxDrawPointSymbols->setChecked(svg->drawPointSymbols());
    ui->checkBoxDrawPointIDs    ->setChecked(svg->drawPointIDs());
    ui->checkBoxDrawEllipses    ->setChecked(svg->drawEllipses());
    ui->checkBoxDrawObservations->setChecked(svg->drawObservations());
    ui->checkBoxDrawAxes        ->setChecked(svg->drawAxes());

    ui->doubleSpinBoxFontSize   ->setValue(svg->fontSize());
    ui->doubleSpinBoxSymbolSize ->setValue(svg->symbolSize());
    ui->doubleSpinBoxStrokeWidth->setValue(svg->strokeWidth());

    ui->comboBoxFixedSymbol      ->setCurrentIndex(pointsymbols.indexOf(svg->fixedSymbol().c_str()));
    ui->comboBoxConstrainedSymbol->setCurrentIndex(pointsymbols.indexOf(svg->constrainedSymbol().c_str()));
    ui->comboBoxFreeSymbol       ->setCurrentIndex(pointsymbols.indexOf(svg->freeSymbol().c_str()));

    ui->comboBoxFixedFill      ->setCurrentIndex(pointfill.indexOf(svg->fixedFill().c_str()));
    ui->comboBoxConstrainedFill->setCurrentIndex(pointfill.indexOf(svg->constrainedFill().c_str()));
    ui->comboBoxFreeFill       ->setCurrentIndex(pointfill.indexOf(svg->freeFill().c_str()));
}

void DrawSettings::on_buttonBox_accepted()
{
    svg->setDrawPointSymbols(ui->checkBoxDrawPointSymbols->isChecked());
    svg->setDrawPointIDs    (ui->checkBoxDrawPointIDs    ->isChecked());
    svg->setDrawEllipses    (ui->checkBoxDrawEllipses    ->isChecked());
    svg->setDrawObservations(ui->checkBoxDrawObservations->isChecked());
    svg->setDrawAxes        (ui->checkBoxDrawAxes        ->isChecked());

    svg->setFontSize   (ui->doubleSpinBoxFontSize   ->value());
    svg->setSymbolSize (ui->doubleSpinBoxSymbolSize ->value());
    svg->setStrokeWidth(ui->doubleSpinBoxStrokeWidth->value());

    svg->setFixedSymbol      (ui->comboBoxFixedSymbol      ->currentText().toStdString());
    svg->setConstrainedSymbol(ui->comboBoxConstrainedSymbol->currentText().toStdString());
    svg->setFreeSymbol       (ui->comboBoxFreeSymbol       ->currentText().toStdString());

    svg->setFixedFill      (ui->comboBoxFixedFill      ->currentText().toStdString());
    svg->setConstrainedFill(ui->comboBoxConstrainedFill->currentText().toStdString());
    svg->setFreeFill       (ui->comboBoxFreeFill       ->currentText().toStdString());

    emit redraw();
}

void DrawSettings::on_buttonBox_clicked(QAbstractButton *button)
{
    QString text = button->text();
    if (text == tr("Apply"))
    {
        on_buttonBox_accepted();
    }
    else if (text == tr("&Close"))
    {
        close();
    }
    else if (text == tr("Restore Defaults"))
    {
        svg->restoreDefaults();
        readSvgValues();
    }
    else if (text == tr("Reset"))
    {
        //svg->restoreDefaults();

        svg->setDrawPointSymbols(r_drawPointSymbols);
        svg->setDrawPointIDs(r_drawPointIDs);
        svg->setDrawEllipses(r_drawEllipses);
        svg->setDrawObservations(r_drawObservations);
        svg->setDrawAxes(r_drawAxes);

        svg->setFontSize(r_fontSize);
        svg->setSymbolSize(r_symbolSize);
        svg->setStrokeWidth(r_strokeWidth);

        svg->setFixedSymbol(r_fixedSymbol);
        svg->setConstrainedSymbol(r_constrainedSymbol);
        svg->setFreeSymbol(r_freeSymbol);

        svg->setFixedFill(r_fixedFill);
        svg->setConstrainedFill(r_constrainedFill);
        svg->setFreeFill(r_freeFill);

        readSvgValues();
    }
    else
    {
        qDebug() << __FILE__ << __LINE__ << "unknown button" << button->text();
    }

    emit redraw();
}
