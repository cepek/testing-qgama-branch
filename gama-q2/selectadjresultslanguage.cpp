#include "selectadjresultslanguage.h"
#include "ui_selectadjresultslanguage.h"
#include "constants.h"
#include "gamaq2controlpanel.h"

SelectAdjResultsLanguage::SelectAdjResultsLanguage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectAdjResultsLanguage)
{
    ui->setupUi(this);

    ui->comboBox->insertItems(0, GamaQ2::languages);
    ui->label2->setText(GamaQ2::currentLanguage);
}

SelectAdjResultsLanguage::~SelectAdjResultsLanguage()
{
    delete ui;
}

void SelectAdjResultsLanguage::on_buttonBox_accepted()
{
    QString code = ui->comboBox->currentText();
    if (code != GamaQ2::currentLanguage)
    {
       GamaQ2ControlPanel* panel = dynamic_cast<GamaQ2ControlPanel*>(parent());
       if (panel == 0) return;

       panel->set_adjustment_results_language(code);
    }
}
