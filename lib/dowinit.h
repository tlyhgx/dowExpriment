#ifndef DOWINIT_H
#define DOWINIT_H

#include <QObject>
#include <QSerialPort>
#include "Sensor.h"



class DowInit : public QObject
{
    Q_OBJECT
public:
    explicit DowInit(QObject *parent = nullptr);
public:
    struct PlcMemoryAddress{
        int signal=4097;   //信号地址,M地址，PLC集中在一起另外配置
//        int signalNum=20;   //信号个数
    };

     PlcMemoryAddress plcMemoryAddress;

     struct ModbusSetting{
         QString portName="COM1";
         int parity = QSerialPort::NoParity;
         int baud = QSerialPort::Baud9600;
         int dataBits = QSerialPort::Data8;
         int stopBits = QSerialPort::OneStop;

         int responseTime = 1000;
         int numberOfRetries = 3;
     };
     ModbusSetting modbusSetting;

     //信号数组的成员数，从最大偏移值获取
    int getSignalValsNum() ;

    QVector<Sensor*> signalVals;
    void addSensor();


    int getSignalReadCycle() const;

    int getRealTimeCurve_x_count() const;
    void setRealTimeCurve_x_count(int value);

signals:

private:
    int signalValsNum;
    //信号读取周期（ms）
    int signalReadCycle;

    //实时曲线的x轴个数
    int realTimeCurve_x_count;



};

#endif // DOWINIT_H
