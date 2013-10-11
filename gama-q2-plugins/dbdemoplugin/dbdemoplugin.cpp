#include <QtPlugin>
#include <QFrame>
#include <QGridLayout>
#include <QLineEdit>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

#include "dbdemoplugin.h"

#include <QDebug>

DBdemoPlugin::DBdemoPlugin()
{
}

QString DBdemoPlugin::getName()
{
    return "DB demo plugin";
}

QWidget* DBdemoPlugin::create()
{
    QSqlDatabase db = QSqlDatabase::database("connection_implicit_db");
    if (!db.isOpen())
    {
        QMessageBox::critical(0, tr("DB demo plugin"),
                              tr("Database is not open, the plugin cannot be started"));
        return 0;
    }

    return getFrame();
}

QFrame* DBdemoPlugin::getFrame()
{
    frame = new QFrame;
    if (frame) {
        frame->setWindowTitle(tr("DB demo plugin"));

        tableView = new QTableView(frame);
        tableView->setMinimumSize(400,250);

        edit = new QLineEdit(frame);

        QGridLayout* grid = new QGridLayout(frame);
        grid->addWidget(edit);
        grid->addWidget(tableView);
        frame->setLayout(grid);
        frame->show();

        model = new QSqlQueryModel(frame);

        selectData();
        edit->setText(tr("write your search pattern here ..."));

        connect(edit, SIGNAL(editingFinished()), SLOT(selectData()));
    }

    return frame;
}

void DBdemoPlugin::selectData()
{
    QString sql =
            "SELECT   conf_name, COUNT(x) AS \"COUNT(x,y)\", "
            "         COUNT(z) AS \"COUNT(z)\" "
            "FROM     gnu_gama_local_configurations JOIN "
            "         gnu_gama_local_points USING (conf_id) "
            "WHERE    conf_name LIKE '%1%' "
            "GROUP BY conf_id, conf_name "
            "ORDER BY conf_name ASC ";

    QSqlDatabase db = QSqlDatabase::database("connection_implicit_db");
    model->setQuery(sql.arg(edit->text().simplified()), db);
    tableView->setModel(model);
}

Q_EXPORT_PLUGIN2(dbdemoplugin, DBdemoPlugin)
