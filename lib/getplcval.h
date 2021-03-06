#ifndef GETPLCVAL_H
#define GETPLCVAL_H

#include <QObject>
#include "dowinit.h"
#include "mymodbus.h"
#include "db_adjust_analog.h"
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
    void ask_alarm_from_plc();
    //启停系统
    void startSys();
    void stopSys();
    QVariantList getParaVals() const;

    int getAlarms() const;

    void get_adjust_analog_vals();

public slots:
    void recieveReply(QModbusDataUnit dataUnit);
    void askOtherSignalVals();
    void askTempSignalVals();
    void askOutPutStateVals();
signals:
   void otherSignalValChanged(QVariantList signalVals);
   void tempSignalValChanged(QVariantList tempSignalVals);
   void paraValsChanged(QVariantList paraVals);
   void alarmsChanged(int previous_alarms,int just_alarms);
   void outPutStateValChanged(QVariantList outPutStateVals);
private:

   DowInit* dowInit;
   MyModbus* myModbus;

   //温度修正值组
   QVariantList adjust_analog_vals;


   QVariantList m_signalVals;
   QVariantList m_tempSignalVals;
   QVariantList m_paraVals;
   int m_alarms;
   int m_outPutStates;
};

#endif // GETPLCVAL_H
