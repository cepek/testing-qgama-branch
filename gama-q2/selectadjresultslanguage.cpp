#include "selectadjresultslanguage.h"
#include "ui_selectadjresultslanguage.h"
#include "constants.h"
#include "gamaq2controlpanel.h"
#include <QLabel>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QVBoxLayout>

SelectAdjResultsLanguage::SelectAdjResultsLanguage(QWidget *parent) :
    QDialog(parent)
{
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                           | QDialogButtonBox::Cancel);
    comboBox = new QComboBox;
    label = new QLabel;
    comboBox->insertItems(0, GamaQ2::languages);
    label->setText(GamaQ2::currentLanguage);

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow(tr("Current language ISO 639-1 code"), label);
    formLayout->addRow(tr("New language"), comboBox);

    QVBoxLayout* vboxLayout = new QVBoxLayout;
    vboxLayout->addLayout(formLayout);
    vboxLayout->addWidget(buttonBox);
    setLayout(vboxLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, [this](){on_buttonBox_accepted();});
    connect(buttonBox, &QDialogButtonBox::rejected, [this](){reject();});
}

SelectAdjResultsLanguage::~SelectAdjResultsLanguage()
{
}

void SelectAdjResultsLanguage::on_buttonBox_accepted()
{
    QString code = comboBox->currentText();
    if (code != GamaQ2::currentLanguage)
    {
       GamaQ2ControlPanel* panel = dynamic_cast<GamaQ2ControlPanel*>(parent());
       if (panel == 0) return;

       panel->set_adjustment_results_language(code);
    }

    accept();
}
