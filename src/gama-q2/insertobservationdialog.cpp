#include "insertobservationdialog.h"
#include "ui_insertobservationdialog.h"

InsertObservationDialog::InsertObservationDialog(QString cluster_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertObservationDialog),
    clusterName(cluster_name)
{
    ui->setupUi(this);
}

InsertObservationDialog::~InsertObservationDialog()
{
    delete ui;
}

int InsertObservationDialog::position() const
{
    return 0;
}

const QStringList& InsertObservationDialog::observationNames() const
{
    return obsNames;
}
