#include "adjustmentresults.h"
#include "ui_adjustmentresults.h"
#include <gnu_gama/local/html.h>
#include <gnu_gama/local/network.h>

#include <QPrinter>
#include <QDebug>

AdjustmentResults::AdjustmentResults(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdjustmentResults),
    html(0)
{
    qDebug() << "AdjustmentResults::AdjustmentResults" << __FILE__ << __LINE__;
    ui->setupUi(this);
}

AdjustmentResults::~AdjustmentResults()
{
    delete ui;
    delete html;
}

void AdjustmentResults::set_local_network(GNU_gama::local::LocalNetwork *local_network)
{
    delete html;
    html = new GNU_gama::local::GamaLocalHTML(local_network);
}

void AdjustmentResults::update_adjustment_results()
{
    if (html == 0) return;

    html->exec();
    const std::string& utf8 = html->str();

    ui->textEdit->clear();
    ui->textEdit->insertHtml(QString::fromUtf8(utf8.c_str(), utf8.length()));
}

QString AdjustmentResults::getHtmlUtf8() const
{
    return QString::fromUtf8(html->str().c_str());
}
