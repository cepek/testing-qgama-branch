#include "gamaq2help.h"

#include <QTextEdit>
#include <QFile>
#include <QDebug>

/* The C++11 standard §6.7.4:
 *           If control enters the declaration concurrently while the variable
 *           is being initialized, the concurrent execution shall wait for
 *           completion of the initialization.
 */
GamaQ2help* GamaQ2help::get()
{
    static GamaQ2help help;
    return &help;
}


// private constructor

GamaQ2help::GamaQ2help(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("gama-q2 help"));

    QFile file(":/help/gama-q2.html");
    file.open(QIODevice::ReadOnly);
    QString text = file.readAll();

    auto edit = new QTextEdit;
    edit->setMinimumSize(500,300);
    edit->setText(text);
    edit->setReadOnly(true);

    setCentralWidget(edit);
}
