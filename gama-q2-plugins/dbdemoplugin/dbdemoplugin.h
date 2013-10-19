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
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.gnu.gama.gama-q2.DbInterface/1.0")
#endif
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
    void selectData(QString str);
};

#endif // DBDEMO_H
