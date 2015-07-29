#ifndef GAMAQ2HELP_H
#define GAMAQ2HELP_H

#include <QMainWindow>

class GamaQ2help : public QMainWindow
{
    Q_OBJECT
public:

     static GamaQ2help* get();

private:
     explicit GamaQ2help(QWidget *parent = 0);
};

#endif // GAMAQ2HELP_H
