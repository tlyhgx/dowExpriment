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
    static float parseInt2Float(int x_high,int x_low);
    QVariantList getSignalVals() const;
    QVariantList getTempSignalVals() const;

public slots:
    void recieveReply(QModbusDataUnit dataUnit);
    void askOtherSignalVals();
    void askTempSignalVals();
signals:
   void otherSignalValChanged(QVariantList signalVals);
   void tempSignalValChanged(QVariantList tempSignalVals);
private:

   DowInit* dowInit;
   MyModbus* myModbus;
   QVariantList m_signalVals;
   QVariantList m_tempSignalVals;
};

#endif // GETPLCVAL_H
