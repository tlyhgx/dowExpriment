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
    static vector<int16_t> parseFloat2Int(float input_float);
    QVariantList getSignalVals() const;
    QVariantList getTempSignalVals() const;
    //设置参数到PLC
    void setPara_to_plc(int startAddress,QList<Para_with_plc> paras);

    void askPara_from_plc(int startAddress,QList<Para_with_plc>paras);
    QVariantList getParaVals() const;

public slots:
    void recieveReply(QModbusDataUnit dataUnit);
    void askOtherSignalVals();
    void askTempSignalVals();
signals:
   void otherSignalValChanged(QVariantList signalVals);
   void tempSignalValChanged(QVariantList tempSignalVals);
   void paraValsChanged(QVariantList paraVals);
private:

   DowInit* dowInit;
   MyModbus* myModbus;
   QVariantList m_signalVals;
   QVariantList m_tempSignalVals;
   QVariantList m_paraVals;
};

#endif // GETPLCVAL_H
