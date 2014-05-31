#ifndef SELECTADJRESULTSLANGUAGE_H
#define SELECTADJRESULTSLANGUAGE_H

#include <QDialog>

namespace Ui {
class SelectAdjResultsLanguage;
}

class SelectAdjResultsLanguage : public QDialog
{
    Q_OBJECT

public:
    explicit SelectAdjResultsLanguage(QWidget *parent = 0);
    ~SelectAdjResultsLanguage();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SelectAdjResultsLanguage *ui;
};

#endif // SELECTADJRESULTSLANGUAGE_H
