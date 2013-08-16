#include "insertclusterdialog.h"
#include "ui_insertclusterdialog.h"
#include "constants.h"

InsertClusterDialog::InsertClusterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertClusterDialog)
{
    ui->setupUi(this);

    ui->comboBoxClusterName->addItem(GamaQ2::obsClusterName);
    ui->comboBoxClusterName->addItem(GamaQ2::xyzClusterName);
    ui->comboBoxClusterName->addItem(GamaQ2::hdfClusterName);
    ui->comboBoxClusterName->addItem(GamaQ2::vecClusterName);

    ui->comboBoxPosition->addItem("Last item in the combo list");
    ui->comboBoxPosition->addItem("After selected cluster");
    ui->comboBoxPosition->addItem("Before selected cluseter");
    ui->comboBoxPosition->addItem("First item in the cluster list");
}

InsertClusterDialog::~InsertClusterDialog()
{
    delete ui;
}

QString InsertClusterDialog::clusterName() const
{
    return ui->comboBoxClusterName->currentText();
}

int InsertClusterDialog::position() const
{
    return ui->comboBoxPosition->currentIndex();
}
