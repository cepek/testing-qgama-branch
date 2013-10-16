#include <QApplication>
#include "gamaq2controlpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GamaQ2ControlPanel w;
    w.show();

    return a.exec();
}
