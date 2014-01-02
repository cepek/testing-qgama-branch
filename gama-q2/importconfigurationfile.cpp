#include "importconfigurationfile.h"
#include "ui_importconfigurationfile.h"
#include "constants.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

// headers from gala-local-xml2sql.cpp
#include <gnu_gama/local/localnetwork2sql.h>
#include <gnu_gama/local/network_gso.h>
#include <gnu_gama/exception.h>
#include <sstream>
#include <fstream>
#include <cctype>

ImportConfigurationFile::ImportConfigurationFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportConfigurationFile)
{
    ui->setupUi(this);

    setWindowTitle(tr("Import XML input data"));
    setWindowModality(Qt::ApplicationModal);
}

ImportConfigurationFile::~ImportConfigurationFile()
{
    delete ui;
}

void ImportConfigurationFile::exec()
{
    QFileDialog fileDialog(0,trUtf8("Open XML Input File"));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    QStringList filters;
    filters << tr("Gama XML input files (*.xml *.gkf)")
            << tr("Any files (*)");
    fileDialog.setNameFilters(filters);
    fileDialog.setViewMode(QFileDialog::Detail);

    if (!fileDialog.exec()) return;

    file = fileDialog.selectedFiles()[0];

    show();

    configure();
}

void ImportConfigurationFile::configure()
{
    QSqlDatabase db = QSqlDatabase::database(GamaQ2::connection_implicit_db);
    QSqlQuery query(db);

    {
        ui->tableWidget_ExistingConfigurationNames->setColumnCount(1);

        QHeaderView* hv = new QHeaderView(Qt::Horizontal, ui->tableWidget_ExistingConfigurationNames);
        ui->tableWidget_ExistingConfigurationNames->setHorizontalHeader(hv);
        hv->setStretchLastSection(true);
        hv->setVisible(false);
        ui->tableWidget_ExistingConfigurationNames->
                setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Existing Configuration Names")));

        query.exec("SELECT conf_name "
                   "FROM   gnu_gama_local_configurations "
                   "ORDER BY conf_name DESC ");
        while (query.next())
        {
            ui->tableWidget_ExistingConfigurationNames->insertRow(0);

            QString conf = query.value(0).toString();
            QTableWidgetItem* item = new QTableWidgetItem(conf);
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget_ExistingConfigurationNames->setItem(0,0,item);
        }
    }

    const QString basename = QFileInfo(file).baseName();
    ui->label_File->setText(file);
    ui->lineEdit_ConfigurationName->setText(basename);
}

void ImportConfigurationFile::on_pushButton_Cancel_clicked()
{
    close();
}

void ImportConfigurationFile::on_lineEdit_ConfigurationName_textChanged(const QString &arg1)
{
    const QRegExp whitespaces("\\s");
    ui->lineEdit_ConfigurationName->setText(QString(arg1).remove(whitespaces));

    bool found  = false;
    int  row  = 0;
    int  rows = ui->tableWidget_ExistingConfigurationNames->rowCount();
    for (int i=rows-1; i>=0; i--)
    {
        QString item = ui->tableWidget_ExistingConfigurationNames->item(i, 0)->text();
        if (item.startsWith(arg1)) row = i;
        if (item == arg1)
        {
            found = true;
            break;
        }
    }

    ui->tableWidget_ExistingConfigurationNames->selectRow(row);
    ui->pushButton_Import->setEnabled(!found);
}

void ImportConfigurationFile::on_pushButton_Import_clicked()
{
    std::stringstream sql;

    try {
        const QString     qnm = ui->label_File->text();
        const std::string snm = qnm.toUtf8().data();
        std::ifstream xml(snm.c_str());

        const QString qconfname = ui->lineEdit_ConfigurationName->text();
        GNU_gama::local::LocalNetwork_gso lnet;
        GNU_gama::local::LocalNetwork2sql imp(lnet);
        imp.readGkf(xml);
        imp.write  (sql, qconfname.toUtf8().data());
    }
    catch (...)
    {

    }

    QSqlDatabase db = QSqlDatabase::database(GamaQ2::connection_implicit_db);
    QSqlQuery query(db);

    db.transaction();

    QString str;
    std::string text;
    while(std::getline(sql, text))
    {
        if (text == "begin;") continue;
        if (text == "commit;") continue;

        bool EndOfSQL = false;
        for (std::string::const_reverse_iterator i=text.rbegin(), e=text.rend(); i!=e; ++i)
            if (!std::isspace(*i))
            {
                if (*i == ';')
                {
                    EndOfSQL = true;
                    break;
                }
            }

        str += QString::fromUtf8(text.c_str());
        str += "\n";

        if (EndOfSQL)
        {
            query.exec(str);
            if (query.lastError().isValid())
            {
                QMessageBox::critical(this, tr("Database error"),
                                      query.lastError().databaseText() + "\n" + str);
                db.rollback();
                close();
                return;
            }
            str.clear();
        }
    }

    db.commit();
    close();
}
