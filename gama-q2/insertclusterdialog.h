#ifndef INSERTCLUSTERDIALOG_H
#define INSERTCLUSTERDIALOG_H

#include <QDialog>

namespace Ui {
class InsertClusterDialog;
}

class InsertClusterDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InsertClusterDialog(QWidget *parent = 0);
    ~InsertClusterDialog();

    QString clusterName() const;
    int     position() const;
    
private:
    Ui::InsertClusterDialog *ui;
};

#endif // INSERTCLUSTERDIALOG_H
