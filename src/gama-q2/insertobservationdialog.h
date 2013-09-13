#ifndef INSERTOBSERVATIONDIALOG_H
#define INSERTOBSERVATIONDIALOG_H

#include "observationtablemodel.h"
#include <QDialog>
#include <QSet>

namespace Ui {
class InsertObservationDialog;
}

class QLineEdit;
class QComboBox;

namespace GNU_gama { namespace local {
    class Observation;
}}

class InsertObservationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InsertObservationDialog(QString cluster_name, QWidget *parent = 0);
    ~InsertObservationDialog();

    int position() const;
    const QStringList& observationNames() const;

    // InsertObservationDialog is a friend class of ObservationTableMode which defines
    // private class ObsInfo
    typedef ObservationTableModel::ObsInfo ObsInfo;
    const   QList<ObsInfo>& obsInfo;

public slots:
    void accept();

private:
    Ui::InsertObservationDialog *ui;

    bool acceptDegrees;
    bool isObsAngle;
    QString clusterName;
    QStringList obsNames;

    QComboBox* comboObservation;
    QComboBox* comboPosition;

    QLineEdit* lineEditFrom;
    QLineEdit* lineEditTo;
    QLineEdit* lineEditValue;
    QString    standpoint, target1, target2;

    QLineEdit* lineEditXdiff;
    QLineEdit* lineEditYdiff;
    QLineEdit* lineEditZdiff;

    QLineEdit* lineEditHdiff;

    QList<ObsInfo> obsinfo;

    bool OK;
    QSet<QString> tags;
    QString html;

    void setWarning(QString tag, QString warning);
    void getPointID(QString tag, QLineEdit* edit, bool isTarget=false);
    void getDouble (QString tag, QLineEdit* edit, double& val, bool positive=false);
};

#endif // INSERTOBSERVATIONDIALOG_H
