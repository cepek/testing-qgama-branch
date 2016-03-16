#ifndef SELECTADJRESULTSLANGUAGE_H
#define SELECTADJRESULTSLANGUAGE_H

#include <QDialog>

class QComboBox;
class QLabel;
class QDialogButtonBox;

class SelectAdjResultsLanguage : public QDialog
{
    Q_OBJECT

public:
    explicit SelectAdjResultsLanguage(QWidget *parent = 0);
    ~SelectAdjResultsLanguage();

private slots:
    void on_buttonBox_accepted();

private:
    QLabel* label {nullptr};
    QComboBox* comboBox {nullptr};
    QDialogButtonBox* buttonBox {nullptr};
};

#endif // SELECTADJRESULTSLANGUAGE_H
