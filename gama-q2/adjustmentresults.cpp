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

#include "adjustmentresults.h"
#include "ui_adjustmentresults.h"
#include <gnu_gama/local/html.h>
#include <gnu_gama/local/network.h>

#include <QDebug>

AdjustmentResults::AdjustmentResults(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdjustmentResults),
    html(0)
{
    qDebug() << "***  AdjustmentResults" << __FILE__ << __LINE__;
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

AdjustmentResults::~AdjustmentResults()
{
    delete ui;
    delete html;
}

void AdjustmentResults::set_local_network(GNU_gama::local::LocalNetwork *local_network)
{
    delete html;
    html = new GNU_gama::local::GamaLocalHTML(local_network);
}

void AdjustmentResults::update_adjustment_results()
{
    if (html == 0) return;

    html->exec();
    const std::string& utf8 = html->str();

    ui->textEdit->clear();
    ui->textEdit->insertHtml(QString::fromUtf8(utf8.c_str(), utf8.length()));
}

QString AdjustmentResults::getHtmlUtf8() const
{
    return QString::fromUtf8(html->str().c_str());
}
