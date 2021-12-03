#ifndef GETPLCVAL_H
#define GETPLCVAL_H

#include <QObject>
#include "dowinit.h"
#include "mymodbus.h"
#include <QtCore>

class GetPlcVal : public QObject
{
    Q_OBJECT
public:
    explicit GetPlcVal(DowInit *dowInit,MyModbus *mymodbus,QObject *parent = nullptr);
public slots:
   void askSignalVals();
signals:
private:
   DowInit *dowInit;
   MyModbus *myModbus;
};

#endif // GETPLCVAL_H
