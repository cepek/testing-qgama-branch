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

    ui->comboBoxPosition->addItem(tr("Last item in the cluster list"));
    ui->comboBoxPosition->addItem(tr("After the selected cluster"));
    ui->comboBoxPosition->addItem(tr("Before the selected cluster"));
    ui->comboBoxPosition->addItem(tr("First item in the cluster list"));
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
