#ifndef DBDEMO_H
#define DBDEMO_H

#include <QObject>
#include "gamaq2interfaces.h"

class QFrame;
class QLineEdit;
class QTableView;
class QSqlQueryModel;

class DBdemoPlugin : public QObject, DbInterface
{
    Q_OBJECT
    Q_INTERFACES(DbInterface)

public:
    DBdemoPlugin();

    QString getName();
    QWidget* create();

private:
    QFrame* getFrame();

    QFrame     *frame;
    QLineEdit  *edit;
    QTableView *tableView;
    QSqlQueryModel *model;

private slots:
    void selectData();
};

#endif // DBDEMO_H
