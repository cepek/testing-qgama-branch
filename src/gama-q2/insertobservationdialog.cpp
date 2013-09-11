#include "insertobservationdialog.h"
#include "ui_insertobservationdialog.h"
#include "constants.h"
#include "gnu_gama/local/observation.h"

#include <QLineEdit>
#include <QDebug>

InsertObservationDialog::InsertObservationDialog(QString cluster_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertObservationDialog),
    obsInfo(obsinfo),
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
    return ui->comboBoxPosition->currentIndex();
}

const QStringList& InsertObservationDialog::observationNames() const
{
    return obsNames;
}

void InsertObservationDialog::accept()
{
    using namespace GNU_gama::local;
    GNU_gama::local::Observation* obs1 = 0;
    GNU_gama::local::Observation* obs2 = 0;
    GNU_gama::local::Observation* obs3 = 0;

    OK = true;
    tags.clear();
    html.clear();
    html += "<dl>";

    try {
        if (clusterName == GamaQ2::obsClusterName) {
            getPointID(tr("From"),  lineEditFrom);
            getPointID(tr("To"),    lineEditTo, true);
            getDouble (tr("Value"), lineEditValue, value);

            QString name = ui->comboBoxObservation->currentText(); name.toStdString().c_str();
            if (OK) try {
                using namespace GNU_gama::local;

                std::string sp(standpoint.toUtf8().data());
                std::string t1(target1.toUtf8().data());
                std::string t2(target2.toUtf8().data());

                ObsInfo info;
                info.rowType = ObservationTableModel::obsRow;

                if (name == GamaQ2::distObsName) {
                    info.observation = obs1 = new Distance(sp, t1, value);
                    info.observationNameIndex = ObservationTableModel::indDist;
                } else if (name == GamaQ2::dirObsName) {
                    info.observation = obs1 = new Direction(sp, t1, value);
                    info.observationNameIndex = ObservationTableModel::indDir;
                } else if (name == GamaQ2::angleObsName) {
                    info.observation = info.angle = new Angle(sp, t1, t2, value);
                    info.angular = true;
                    info.observationNameIndex = ObservationTableModel::indAngle;
                } else if (name == GamaQ2::slopeObsName) {
                    info.observation = obs1 = new S_Distance(sp, t1, value);
                    info.angular = true;
                    info.observationNameIndex = ObservationTableModel::indSdist;
                } else if (name == GamaQ2::zangleObsName) {
                    info.observation = obs1 = new Z_Angle(sp, t1, value);
                    info.angular = true;
                    info.observationNameIndex = ObservationTableModel::indZangle;
                } else
                    throw Exception(tr("unnown observation type in "
                                       "GamaQ2::obsClusterName").toUtf8().data());

                obsinfo.push_back(info);
            }
            catch(const Exception& e) {
                setWarning(name, e.what());
            }
            catch (...) {
                throw;
            }
        }
        else if (clusterName == GamaQ2::xyzClusterName) {

        }
        else if (clusterName == GamaQ2::hdfClusterName) {

        }
        else if (clusterName == GamaQ2::vecClusterName) {

        }
        else {
            setWarning(tr("FATAL"), tr("unknown cluster type"));
            setWarning(tr("FATAL"), tr("this should never happen"));
        }
    }
    catch (...) {
        setWarning(tr("FATAL"), tr("unknown exception"));
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
