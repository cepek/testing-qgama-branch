#ifndef INSERTOBSERVATIONDIALOG_H
#define INSERTOBSERVATIONDIALOG_H

#include <QDialog>
#include <QSet>

namespace Ui {
class InsertObservationDialog;
}

class QLineEdit;

class InsertObservationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InsertObservationDialog(QString cluster_name, QWidget *parent = 0);
    ~InsertObservationDialog();

    int position() const;
    const QStringList& observationNames() const;
    
public slots:
    void accept();

private:
    Ui::InsertObservationDialog *ui;

    QString clusterName;
    QStringList obsNames;

    QLineEdit* lineEditFrom;
    QLineEdit* lineEditTo;
    QLineEdit* lineEditValue;
    QLineEdit* lineEditStdev;
    QString    standpoint, target1, target2;
    double     value, stdev;

    bool OK;
    QSet<QString> tags;
    QString html;

    void setWarning(QString tag, QString warning);
    void getPointID(QString tag, QLineEdit* edit, bool isTarget=false);
    void getDouble (QString tag, QLineEdit* edit, double& val, bool positive=false);
};

#endif // INSERTOBSERVATIONDIALOG_H
