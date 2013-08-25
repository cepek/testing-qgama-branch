#ifndef INSERTOBSERVATIONDIALOG_H
#define INSERTOBSERVATIONDIALOG_H

#include <QDialog>

namespace Ui {
class InsertObservationDialog;
}

class InsertObservationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InsertObservationDialog(QString cluster_name, QWidget *parent = 0);
    ~InsertObservationDialog();

    int position() const;
    const QStringList& observationNames() const;
    
private:
    Ui::InsertObservationDialog *ui;

    QString clusterName;
    QStringList obsNames;
};

#endif // INSERTOBSERVATIONDIALOG_H
