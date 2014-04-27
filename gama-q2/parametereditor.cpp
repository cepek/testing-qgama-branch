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

#include "parametereditor.h"
#include "ui_parametereditor.h"
#include <QMessageBox>
#include <QDebug>

ParameterEditor::ParameterEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterEditor),
    lnet(0)
{
    qDebug() << "***  ParameterEditor" << __FILE__ << __LINE__;
    ui->setupUi(this);

    enableEdit(false);

    ui->label_latitude->hide();
    ui->lineEdit_latitude->hide();
    ui->label_ellipsoid->hide();
    ui->comboBox_ellipsoid->hide();
    this->adjustSize();
}

ParameterEditor::~ParameterEditor()
{
    delete ui;
}

void ParameterEditor::enableEdit(bool edit)
{
    readonly = !edit;

    ui->plainTextEdit->setReadOnly(readonly);

    ui->lineEdit_sigma_apr  ->setEnabled(edit);
    ui->lineEdit_conf_pr    ->setEnabled(edit);
    ui->lineEdit_tol_abs    ->setEnabled(edit);
    ui->comboBox_sigma_act  ->setEnabled(edit);
    ui->checkBox_update_cc  ->setEnabled(edit);
    ui->comboBox_axes_xy    ->setEnabled(edit);
    ui->comboBox_angles     ->setEnabled(edit);
    ui->lineEdit_epoch      ->setEnabled(edit);
    ui->comboBox_algorithm  ->setEnabled(edit);
    ui->comboBox_ang_units  ->setEnabled(edit);
    ui->lineEdit_adj_covband->setEnabled(edit);
    ui->lineEdit_latitude   ->setEnabled(edit && false);
    ui->comboBox_ellipsoid  ->setEnabled(edit && false);
}

void ParameterEditor::connectParameters(GNU_gama::local::LocalNetwork *ln)
{
    lnet = ln;

    ui->plainTextEdit->setPlainText( QString::fromUtf8(lnet->description.c_str()) );
    ui->lineEdit_sigma_apr->setText( QString::number(lnet->apriori_m_0()) );
    ui->lineEdit_conf_pr  ->setText( QString::number( lnet->conf_pr()) );
    ui->lineEdit_tol_abs  ->setText( QString::number(lnet->tol_abs()) );

    if(double epoch = lnet->epoch()) {
        ui->lineEdit_epoch->setText( QString::number(epoch) );
    } else {
        ui->lineEdit_epoch->clear();
    }

    if (lnet->m_0_aposteriori())
        ui->comboBox_sigma_act->setCurrentIndex(0);
    else
        ui->comboBox_sigma_act->setCurrentIndex(1);

    if (lnet->PD.left_handed_angles())
        ui->comboBox_angles->setCurrentIndex(0);
    else
        ui->comboBox_angles->setCurrentIndex(1);

    QString algorithm = lnet->algorithm().c_str();
    int index_alg = 0;
    for (int i=0; i<ui->comboBox_algorithm->count(); i++)
        if (ui->comboBox_algorithm->itemText(i) == algorithm)
        {
            index_alg = i;
            break;
        }
    ui->comboBox_algorithm->setCurrentIndex(index_alg);

    if (lnet->gons())
        ui->comboBox_ang_units->setCurrentIndex(0);
    else
        ui->comboBox_ang_units->setCurrentIndex(1);

    bool bcc = lnet->update_constrained_coordinates();
    ui->checkBox_update_cc->setChecked(bcc);

    ui->lineEdit_adj_covband->setText(QString::number(lnet->adj_covband()));
}

void ParameterEditor::on_plainTextEdit_textChanged()
{
    lnet->description = ui->plainTextEdit->toPlainText().toUtf8().data();
}

void ParameterEditor::on_lineEdit_sigma_apr_editingFinished()
{
    bool ok;
    double value = ui->lineEdit_sigma_apr->text().toDouble(&ok);

    if (ok && value > 0)
    {
        lnet->apriori_m_0(value);
        lnet->update_adjustment();
        return;
    }

    QString adjpar = tr("A priori reference standard deviation");
    if (!ok) QMessageBox::critical(this, adjpar,tr("Conversion error"));
    else     QMessageBox::critical(this, adjpar,tr("Must greater than 0"));

    ui->lineEdit_sigma_apr->setFocus();
}

void ParameterEditor::on_lineEdit_conf_pr_editingFinished()
{
    bool ok;
    double value = ui->lineEdit_conf_pr->text().toDouble(&ok);

    if (ok && value > 0 && value < 1)
    {
        lnet->conf_pr(value);
        lnet->update_adjustment();
        return;
    }

    QString adjpar = tr("Confidence probability used in statistical tests");
    if (!ok) QMessageBox::critical(this, adjpar,tr("Conversion error"));
    else     QMessageBox::critical(this, adjpar,tr("Must from from interval 0 and 1"));

    ui->lineEdit_conf_pr->setFocus();
}

void ParameterEditor::on_lineEdit_tol_abs_editingFinished()
{
    bool ok;
    double value = ui->lineEdit_tol_abs->text().toDouble(&ok);

    if (ok && value > 0)
    {
        lnet->tol_abs(value);
        lnet->update_residuals();
        return;
    }

    QString adjpar = tr("Tolerance for the identification of gross absolute terms");
    if (!ok) QMessageBox::critical(this, adjpar,tr("Conversion error"));
    else     QMessageBox::critical(this, adjpar,tr("Must from greater than 0"));

    ui->lineEdit_tol_abs->setFocus();
}

void ParameterEditor::on_lineEdit_epoch_editingFinished()
{
    if (ui->lineEdit_epoch->text().simplified().isEmpty())
    {
        lnet->set_epoch(0);
        return;
    }

    bool ok;
    double value = ui->lineEdit_epoch->text().toDouble(&ok);

    if (ok)
    {
        lnet->set_epoch(value);
        return;
    }

    QString adjpar = tr("Epoch of the measurement");
    if (!ok) QMessageBox::critical(this, adjpar,tr("Conversion error"));
    //else     QMessageBox::critical(this, adjpar,tr("????"));

    ui->lineEdit_epoch->setFocus();
}

void ParameterEditor::on_lineEdit_latitude_editingFinished()
{
    QMessageBox::warning(this, "Latitude", "Latitude corrections not implemented");
}

void ParameterEditor::on_comboBox_sigma_act_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "a posteriori")
        lnet->set_m_0_aposteriori();
    else
        lnet->set_m_0_apriori();

    lnet->update_adjustment();
}

void ParameterEditor::on_comboBox_axes_xy_currentIndexChanged(const QString &arg1)
{
    using namespace GNU_gama::local;

    LocalCoordinateSystem::CS& lcs = lnet->PD.local_coordinate_system;

    if      (arg1 == "ne") lcs = LocalCoordinateSystem::NE;
    else if (arg1 == "sw") lcs = LocalCoordinateSystem::SW;
    else if (arg1 == "es") lcs = LocalCoordinateSystem::ES;
    else if (arg1 == "wn") lcs = LocalCoordinateSystem::WN;
    else if (arg1 == "en") lcs = LocalCoordinateSystem::EN;
    else if (arg1 == "nw") lcs = LocalCoordinateSystem::NW;
    else if (arg1 == "se") lcs = LocalCoordinateSystem::SE;
    else if (arg1 == "ws") lcs = LocalCoordinateSystem::WS;
    else
         ;

    lnet->update_points();
}

void ParameterEditor::on_comboBox_angles_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "clockwise")
        lnet->PD.setAngularObservations_Lefthanded();
    else
        lnet->PD.setAngularObservations_Righthanded();

    lnet->update_points();
}

void ParameterEditor::on_comboBox_algorithm_currentIndexChanged(const QString &arg1)
{
    lnet->set_algorithm(arg1.toStdString());
}

void ParameterEditor::on_comboBox_ang_units_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "360")
        lnet->set_degrees();
    else
        lnet->set_gons();

    emit angular_units_changed();
}

void ParameterEditor::on_comboBox_ellipsoid_currentIndexChanged(const QString &arg1)
{
    QMessageBox::warning(this, "Ellipsoid", "Ellipsoid selection not implemented");
}

void ParameterEditor::on_checkBox_update_cc_stateChanged(int arg1)
{
    lnet->update_constrained_coordinates(arg1 != 0);
    lnet->update_points();
}

void ParameterEditor::on_lineEdit_adj_covband_editingFinished()
{
    QString s = ui->lineEdit_adj_covband->text().simplified();
    int n = s.toInt();
    if (n == 0) s.clear();
    else if (n < 0) s = "-1";
    ui->lineEdit_adj_covband->setText(s);

    lnet->set_adj_covband(n);
}
