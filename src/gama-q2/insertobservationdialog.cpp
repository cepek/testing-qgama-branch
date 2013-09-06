#include "insertobservationdialog.h"
#include "ui_insertobservationdialog.h"
#include "constants.h"

#include <QLineEdit>
#include <QDebug>

InsertObservationDialog::InsertObservationDialog(QString cluster_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertObservationDialog),
    clusterName(cluster_name)
{
    ui->setupUi(this);

    ui->warnings->hide();
    ui->warnings->setReadOnly(true);

    ui->comboBoxPosition->addItem(tr("Last Observation in the Cluster"));
    ui->comboBoxPosition->addItem(tr("After the Selected Obesrvation"));
    ui->comboBoxPosition->addItem(tr("Before the Slecter Observation"));
    ui->comboBoxPosition->addItem(tr("First observation in the Cluster"));

    if (clusterName == GamaQ2::obsClusterName)
    {
        // height differences are not included on purpose, they should
        // be used only in hdf cluster, though they are allowed in XML input (.gkf)
        ui->comboBoxObservation->addItem(GamaQ2::distObsName);
        ui->comboBoxObservation->addItem(GamaQ2::dirObsName);
        ui->comboBoxObservation->addItem(GamaQ2::angleObsName);
        ui->comboBoxObservation->addItem(GamaQ2::slopeObsName);
        ui->comboBoxObservation->addItem(GamaQ2::zangleObsName);

        ui->formLayout->addRow(tr("From" ), lineEditFrom  = new QLineEdit(this));
        ui->formLayout->addRow(tr("To"   ), lineEditTo    = new QLineEdit(this));
        ui->formLayout->addRow(tr("Value"), lineEditValue = new QLineEdit(this));
        ui->formLayout->addRow(tr("Stdev"), lineEditStdev = new QLineEdit(this));
    }
    else if (clusterName == GamaQ2::xyzClusterName)
    {

    }
    else if (clusterName == GamaQ2::hdfClusterName)
    {

    }
    else if (clusterName == GamaQ2::vecClusterName)
    {

    }
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

void InsertObservationDialog::accept()
{
    OK = true;
    tags.clear();
    html.clear();
    html += "<dl>";

    if (clusterName == GamaQ2::obsClusterName)
    {
        getPointID(tr("From"),  lineEditFrom);
        getPointID(tr("To"),    lineEditTo, true);
        getDouble (tr("Value"), lineEditValue, value);
        getDouble (tr("Stdev"), lineEditStdev, stdev, true);
    }
    else if (clusterName == GamaQ2::xyzClusterName)
    {

    }
    else if (clusterName == GamaQ2::hdfClusterName)
    {

    }
    else if (clusterName == GamaQ2::vecClusterName)
    {

    }
    else
    {
        setWarning(tr("FATAL"), tr("unknown cluster type"));
        setWarning(tr("FATAL"), tr("this should never happen"));
    }

    html += "</dl>";
    ui->warnings->clear();
    ui->warnings->insertHtml(html);
    ui->warnings->moveCursor(QTextCursor::Start);

    if (OK) done(Accepted);
    else    ui->warnings->show();
}

void InsertObservationDialog::getPointID(QString tag, QLineEdit *edit, bool isTarget)
{
    if (edit->text().isEmpty())
        setWarning(tag,   tr("Point ID is empty"));
    if (!isTarget && edit->text().contains(";"))
        setWarning(tag, tr("Point ID contains semicolon (;)"));
    if (isTarget && !edit->text().isEmpty() &&
        !lineEditTo->text().contains(";") &&
        ui->comboBoxObservation->currentText() == GamaQ2::angleObsName)
        setWarning(tag, tr("Target field does not contain semicolon (;)"
                                ", for an angle semilocon separates backsight and foresight IDs"));

    if (isTarget && ui->comboBoxObservation->currentText() == GamaQ2::angleObsName)
    {
        QStringList list = edit->text().split(QRegExp("\\s*;\\s*"));
        qDebug() << list;
        if (list.size() != 2 || list[0].isEmpty() || list[1].isEmpty())
        {
            setWarning(tag, tr("An angle must have two target IDs separated by one semicolon"));
            target1.clear();
            target2.clear();
        }
        else
        {
            target1 = list[0].simplified();
            target2 = list[1].simplified();
        }
    }
    else if (isTarget)
    {
        target1 = edit->text().simplified();
        target2.clear();
    }
    else
    {
        standpoint = edit->text().simplified();
    }

    QString tst = isTarget ? target1 + target2 : standpoint;
    if (tst.contains(QRegExp("\\s")))
        setWarning(tag, tr("ID must not contain whitespaces"));

    qDebug() << standpoint << target1 << target2;
}

void InsertObservationDialog::setWarning(QString tag, QString warning)
{
    OK = false;
    if (!tags.contains(tag))
    {
        html.append("<dt>" + tag + "</dt>\n");
    }
    tags.insert(tag);
    html.append("<dd>" + warning + "</dd>\n");
}

void InsertObservationDialog::getDouble(QString tag, QLineEdit* edit, double &val, bool positive)
{
    bool good = true;
    val = edit->text().toDouble(&good);
    if (!good) setWarning(tag, tr("Not a numeric value"));

    if (good & positive & val <= 0) setWarning(tag, "Value must be positive");
}
