#include "covariancematrixeditor.h"
#include "ui_covariancematrixeditor.h"
#include <cstdlib>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDebug>

CovarianceMatrixEditor::CovarianceMatrixEditor(GNU_gama::local::CovMat& cov, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CovarianceMatrixEditor),
    covmat(cov)
{
    ui->setupUi(this);
    on_comboBox_currentIndexChanged(0);

    //ui->lineEditColumn->setValidator(new QIntValidator);

    connect(ui->lineEditRow,    SIGNAL(editingFinished()), this, SLOT(lineEditRowColumn_editingFinished()));
    connect(ui->lineEditColumn, SIGNAL(editingFinished()), this, SLOT(lineEditRowColumn_editingFinished()));
    connect(ui->lineEditValue,  SIGNAL(editingFinished()), this, SLOT(lineEditingFinished()));
}

CovarianceMatrixEditor::~CovarianceMatrixEditor()
{
    delete ui;
}

void CovarianceMatrixEditor::on_comboBox_currentIndexChanged(int index)
{
    matrixTable = index;
    refresh();
}

void CovarianceMatrixEditor::refresh()
{
    disconnect(ui->tableWidget, SIGNAL(cellChanged(int,int)),
               this, SLOT(on_tableWidget_cellChanged(int,int)));

    ui->tableWidget->clearSelection();
    clearEdits();

    int R = covmat.rows();
    int B = covmat.bandWidth();

    ui->lineEditDimension->setText(QString::number(R));
    ui->lineEditBandWidth->setText(QString::number(B));

    QColor bgc = QColor(230,230,230);  // lighter than Qt::lightGray
    if (matrixTable == showBand)
    {
        ui->tableWidget->setRowCount(covmat.rows());
        ui->tableWidget->setColumnCount(covmat.bandWidth()+1);

        for (int b=0; b<=B; b++)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText(QString::number(b));
            ui->tableWidget->setHorizontalHeaderItem(b, item);
        }

        for (int r=1; r<=R; r++)
            for (int b=0; b<=B; b++)
                if (r+b <= R)
                {
                    QTableWidgetItem* item = new QTableWidgetItem();
                    item->setText(QString::number(covmat(r,r+b), 'g', 16));
                    ui->tableWidget->setItem(r-1,b,item);
                }
                else
                {
                    QTableWidgetItem* item = new QTableWidgetItem(Qt::BackgroundColorRole);
                    item->setBackgroundColor(bgc);
                    item->setFlags(Qt::ItemIsEnabled);
                    ui->tableWidget->setItem(r-1,b,item);
                }
    }
    else
    {
        ui->tableWidget->setRowCount(covmat.rows());
        ui->tableWidget->setColumnCount(covmat.rows());

        for (int c=1; c<=R; c++)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText(QString::number(c));
            ui->tableWidget->setHorizontalHeaderItem(c-1, item);
        }

        for (int r=1; r<=R; r++)
            for (int c=1; c<=R; c++)
                if (std::abs(r-c) <= B)
                {
                    QTableWidgetItem* item = new QTableWidgetItem();
                    item->setText(QString::number(covmat(r,c), 'g', 16));
                    ui->tableWidget->setItem(r-1,c-1,item);
                }
                else
                {
                    QTableWidgetItem* item = new QTableWidgetItem(Qt::BackgroundColorRole);
                    item->setBackgroundColor(bgc);
                    item->setFlags(Qt::ItemIsEnabled);
                    ui->tableWidget->setItem(r-1,c-1,item);
                }
    }

    if (R > 0)
        defaultBackground = ui->tableWidget->item(0,0)->background();
    //else
    //    defaultBackground = QColor(255,255,255);

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)),
            this, SLOT(on_tableWidget_cellChanged(int,int)));
}

void CovarianceMatrixEditor::on_tableWidget_itemSelectionChanged()
{   
    QModelIndex index = ui->tableWidget->selectionModel()->currentIndex();
    if (!index.isValid()) return;

    clearEdits();

    int row = index.row() + 1;
    int col = index.column() + (matrixTable == showBand ? row : 1);
    int bnd = std::abs(row-col);

    if (col > covmat.cols() || bnd > covmat.bandWidth()) return;

    ui->lineEditRow->setText(QString::number(row));
    ui->lineEditColumn->setText(QString::number(col));
    ui->lineEditValue->setText(QString::number(covmat(row,col), 'g', 16));
}


void CovarianceMatrixEditor::clearEdits()
{
    ui->lineEditRow->clear();
    ui->lineEditColumn->clear();
    ui->lineEditValue->clear();
}

void CovarianceMatrixEditor::on_tableWidget_cellChanged(int row, int column)
{
    QTableWidgetItem* item = ui->tableWidget->item(row, column);
    QString text = item->text();

    int r = row + 1;
    int c = column + (matrixTable == showBand ? r : 1);
    double  orig = covmat(r,c);
    bool    ok;
    double  nval = text.toDouble(&ok);

    if (ok)
    {
        covmat(r,c) = nval;
        ui->lineEditValue->setText(text);

        ui->tableWidget->item(column, row)->setBackground(defaultBackground);
        if (matrixTable != showBand)
        {
            ui->tableWidget->item(column, row)->setText(text);
            ui->tableWidget->item(column, row)->setBackground(defaultBackground);
        }
    }
    else
    {
        ui->tableWidget->item(row, column)->setBackground( QColor(255,120,120));
        ui->tableWidget->item(row, column)->setSelected(false);
    }
}

void CovarianceMatrixEditor::lineEditingFinished()
{
    bool okr, okc, okv;
    int r = ui->lineEditRow->text().toInt(&okr);
    int c = ui->lineEditColumn->text().toInt(&okc);

    if (!okr || !okc) return;

    if (std::min(r,c) < 1) return;
    if (std::max(r,c) > covmat.rows()) return;

    if (matrixTable == showBand) c = std::abs(r - c); else c--;
    r--;

    double v = ui->lineEditValue->text().toDouble(&okv);
    if (okv)
    {
        ui->tableWidget->item(r,c)->setText(ui->lineEditValue->text());
    }
    else
    {
        ui->tableWidget->setCurrentCell(r,c);
    }
}


void CovarianceMatrixEditor::lineEditRowColumn_editingFinished()
{
    bool okr, okc;
    int r = ui->lineEditRow->text().toInt(&okr);
    int c = ui->lineEditColumn->text().toInt(&okc);
    if (!okr || !okc) return;

    if (std::min(r,c) < 1) return;
    if (std::max(r,c) > covmat.rows()) return;

    if (matrixTable == showBand) c = std::abs(r - c); else c--;
    r--;
    ui->tableWidget->setCurrentCell(r,c);
}

void CovarianceMatrixEditor::on_lineEditBandWidth_editingFinished()
{
    bool ok;
    int  nbw = ui->lineEditBandWidth->text().toDouble(&ok);
    if (!ok) return;

    if (nbw == covmat.bandWidth()) return;

    if (nbw < 0) nbw = 0;
    if (nbw >= covmat.dim()) nbw = covmat.dim()-1;

    GNU_gama::local::CovMat tmp = covmat;

    covmat.reset(tmp.dim(), nbw);
    covmat.set_zero();

    int R = tmp.dim();
    int B = std::min(tmp.bandWidth(), covmat.bandWidth());

    for (int r=1; r<=R; r++)
        for (int b=r; b<=r+B; b++)
            if (b <= R)
                covmat(r,b) = tmp(r,b);

    refresh();
}
