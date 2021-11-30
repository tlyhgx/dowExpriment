#ifndef MAINBACKEND_H
#define MAINBACKEND_H

#include <QObject>
#include <QVariant>
#include "My_Modbus.h"
#include "dowinit.h"
using namespace std;
class MainBackend : public QObject
{
    Q_OBJECT
public:
    explicit MainBackend(QObject *parent = nullptr);
public:
    Q_INVOKABLE QVariantList askSignalVals();
    void setMyModbus(My_Modbus *myModbus);

    void setDowInit(DowInit *value);

signals:

private:
    My_Modbus* myModbus;
    DowInit* dowInit;
};

#endif // MAINBACKEND_H
