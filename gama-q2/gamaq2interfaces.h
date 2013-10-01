#ifndef GAMAQ2INTERFACES_H
#define GAMAQ2INTERFACES_H

class DbInterface
{
public:
    virtual ~DbInterface() {}
    virtual QString getName() = 0;
    virtual QWidget* create() = 0;
};

Q_DECLARE_INTERFACE(DbInterface, "org.gnu.gama.DbInterface/1.0");

#endif // GAMAQ2INTERFACES_H
