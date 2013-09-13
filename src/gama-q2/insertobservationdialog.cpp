#include "insertobservationdialog.h"
#include "ui_insertobservationdialog.h"
#include "constants.h"
#include <gnu_gama/local/observation.h>
#include <gnu_gama/gon2deg.h>

#include <QComboBox>
#include <QLineEdit>
#include <QDebug>

InsertObservationDialog::InsertObservationDialog(QString cluster_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertObservationDialog),
    obsInfo(obsinfo),
    acceptDegrees(false),
    isObsAngle(false),
    clusterName(cluster_name)
{
    ui->setupUi(this);

    qDebug() << "InsertObservationDialog CTOR" << __FILE__ << __LINE__;

    ui->warnings->hide();
    ui->warnings->setReadOnly(true);

    comboPosition = new QComboBox(this);
    comboPosition->addItem(tr("Last Observation in the Cluster"));
    comboPosition->addItem(tr("After the Selected Obesrvation"));
    comboPosition->addItem(tr("Before the Slecter Observation"));
    comboPosition->addItem(tr("First observation in the Cluster"));

    if (clusterName == GamaQ2::obsClusterName)
    {
        setWindowTitle(tr("Insert observation"));

        // height differences are not included on purpose, they should
        // be used only in hdf cluster, though they are allowed in XML input (.gkf)
        comboObservation = new QComboBox(this);
        comboObservation->addItem(GamaQ2::distObsName);
        comboObservation->addItem(GamaQ2::dirObsName);
        comboObservation->addItem(GamaQ2::angleObsName);
        comboObservation->addItem(GamaQ2::slopeObsName);
        comboObservation->addItem(GamaQ2::zangleObsName);

        ui->formLayout->addRow(tr("Observation"), comboObservation);
        ui->formLayout->addRow(tr("Position"),    comboPosition);
        ui->formLayout->addRow(tr("From" ), lineEditFrom  = new QLineEdit(this));
        ui->formLayout->addRow(tr("To"   ), lineEditTo    = new QLineEdit(this));
        ui->formLayout->addRow(tr("Value"), lineEditValue = new QLineEdit(this));
    }
    else if (clusterName == GamaQ2::xyzClusterName)
    {

    }
    else if (clusterName == GamaQ2::hdfClusterName)
    {
        setWindowTitle(tr("Insert height difference"));

        ui->formLayout->addRow(tr("Position"), comboPosition);
        ui->formLayout->addRow(tr("From" ),    lineEditFrom  = new QLineEdit(this));
        ui->formLayout->addRow(tr("To"   ),    lineEditTo    = new QLineEdit(this));
        ui->formLayout->addRow(tr("H diff"),   lineEditHdiff = new QLineEdit(this));
    }
    else if (clusterName == GamaQ2::vecClusterName)
    {
        setWindowTitle(tr("Insert vector"));

        ui->formLayout->addRow(tr("Position"), comboPosition);
        ui->formLayout->addRow(tr("From" ),    lineEditFrom  = new QLineEdit(this));
        ui->formLayout->addRow(tr("To"   ),    lineEditTo    = new QLineEdit(this));
        ui->formLayout->addRow(tr("X diff"),   lineEditXdiff = new QLineEdit(this));
        ui->formLayout->addRow(tr("Y diff"),   lineEditYdiff = new QLineEdit(this));
        ui->formLayout->addRow(tr("Z diff"),   lineEditZdiff = new QLineEdit(this));
    }
}

InsertObservationDialog::~InsertObservationDialog()
{
    delete ui;
}

int InsertObservationDialog::position() const
{
    return comboPosition->currentIndex();
}

const QStringList& InsertObservationDialog::observationNames() const
{
    return obsNames;
}

void InsertObservationDialog::accept()
{
    using namespace GNU_gama::local;

    OK = true;
    tags.clear();
    html.clear();
    html += "<dl>";

    acceptDegrees = false;
    isObsAngle = false;

    try {
        if (clusterName == GamaQ2::obsClusterName) {

            QString name = comboObservation->currentText();

            if (name==GamaQ2::dirObsName || name ==  GamaQ2::angleObsName || name == GamaQ2::zangleObsName)
            {
                acceptDegrees = true;    // see getDouble()
            }

            if (name ==  GamaQ2::angleObsName)
            {
                isObsAngle = true;       // see getPointID
            }

            double value;
            getPointID(tr("From"),  lineEditFrom);
            getPointID(tr("To"),    lineEditTo, true);
            getDouble (tr("Value"), lineEditValue, value);

            if (OK) try {
                using namespace GNU_gama::local;

                std::string sp(standpoint.toUtf8().data());
                std::string t1(target1.toUtf8().data());
                std::string t2(target2.toUtf8().data());

                ObsInfo info;
                info.rowType = ObservationTableModel::obsRow;

                if (name == GamaQ2::distObsName) {
                    info.observation = new Distance(sp, t1, value);
                    info.observationNameIndex = ObservationTableModel::indDist;
                } else if (name == GamaQ2::dirObsName) {
                    info.observation = new Direction(sp, t1, value*G2R);
                    info.angular = true;
                    info.observationNameIndex = ObservationTableModel::indDir;
                } else if (name == GamaQ2::angleObsName) {
                    info.observation = info.angle = new Angle(sp, t1, t2, value*G2R);
                    info.angular = true;
                    info.observationNameIndex = ObservationTableModel::indAngle;
                } else if (name == GamaQ2::slopeObsName) {
                    info.observation = new S_Distance(sp, t1, value);
                    info.observationNameIndex = ObservationTableModel::indSdist;
                } else if (name == GamaQ2::zangleObsName) {
                    info.observation = new Z_Angle(sp, t1, value*G2R);
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

            double value;
            getPointID(tr("From"),  lineEditFrom);
            getPointID(tr("To"),    lineEditTo, true);
            getDouble (tr("Value"), lineEditHdiff, value);

            if (OK) try {
                using namespace GNU_gama::local;

                QString standpoint = lineEditFrom->text().simplified();
                QString target     = lineEditTo->text().simplified();

                std::string sp(standpoint.toUtf8().data());
                std::string tp(target.toUtf8().data());

                ObsInfo info;
                info.rowType = ObservationTableModel::obsRow;

                info.observation = new H_Diff(sp, tp, value);
                info.observationNameIndex = ObservationTableModel::indHdiff;

                obsinfo.push_back(info);
            }
            catch(const Exception& e) {
                setWarning(comboObservation->currentText(), e.what());
            }
            catch (...) {
                throw;
            }
        }
        else if (clusterName == GamaQ2::vecClusterName) {

            qDebug() << "else if (clusterName == GamaQ2::vecClusterName)" << __FILE__ << __LINE__;
            qDebug() << lineEditFrom << lineEditTo << lineEditXdiff << lineEditYdiff << lineEditZdiff;

            double vecXdiff, vecYdiff, vecZdiff;
            getPointID(tr("From"),   lineEditFrom);
            getPointID(tr("To"),     lineEditTo, true);
            getDouble (tr("X diff"), lineEditXdiff, vecXdiff);
            getDouble (tr("Y diff"), lineEditYdiff, vecYdiff);
            getDouble (tr("Z diff"), lineEditZdiff, vecZdiff);

            if (OK) try {
                using namespace GNU_gama::local;

                QString standpoint = lineEditFrom->text().simplified();
                QString target     = lineEditTo->text().simplified();

                std::string sp(standpoint.toUtf8().data());
                std::string tp(target.toUtf8().data());

                ObsInfo infoXdiff, infoYdiff, infoZdiff;
                infoXdiff.rowType = infoYdiff.rowType = infoZdiff.rowType = ObservationTableModel::obsRow;
                infoXdiff.group = infoYdiff.group = infoZdiff.group = GamaQ2::getUnique();

                infoXdiff.observation = new Xdiff(sp, tp, vecXdiff);
                infoYdiff.observation = new Ydiff(sp, tp, vecYdiff);
                infoZdiff.observation = new Zdiff(sp, tp, vecZdiff);

                infoXdiff.observationNameIndex = ObservationTableModel::indXdiff;
                infoYdiff.observationNameIndex = ObservationTableModel::indYdiff;
                infoZdiff.observationNameIndex = ObservationTableModel::indZdiff;

                obsinfo.push_back(infoXdiff);
                obsinfo.push_back(infoYdiff);
                obsinfo.push_back(infoZdiff);
            }
            catch(const Exception& e) {
                setWarning(comboObservation->currentText(), e.what());
            }
            catch (...) {
                throw;
            }
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
    qDebug() << "InsertObservationDialog::getPointID" << __FILE__ << __LINE__;
    if (edit->text().isEmpty())
        setWarning(tag,   tr("Point ID is empty"));
    if (!isTarget && edit->text().contains(";"))
        setWarning(tag, tr("Point ID contains semicolon (;)"));
    if (isTarget && !edit->text().isEmpty() && !edit->text().contains(";") && isObsAngle)
        setWarning(tag, tr("Target field does not contain semicolon (;)"
                                ", for an angle semilocon separates backsight and foresight IDs"));

    if (isTarget && isObsAngle)
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
    if (!good)
    {
        if (acceptDegrees) good = GNU_gama::deg2gon(edit->text().toStdString(), val);
        if (!good) setWarning(tag, tr("Not a numeric value"));
    }
    if (good & positive & val <= 0) setWarning(tag, "Value must be positive");
}
