#include <QApplication>
#include "gamaq2controlpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon icon(":/img/q2-icon.png");
    a.setWindowIcon(icon);

    GamaQ2ControlPanel w;
    w.show();

    return a.exec();
}
