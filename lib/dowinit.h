#ifndef DOWINIT_H
#define DOWINIT_H

#include <QObject>
#include <QSerialPort>
#include <QSqlDatabase>
#include "Sensor.h"



class DowInit : public QObject
{
    Q_OBJECT
public:
    explicit DowInit(QObject *parent = nullptr);
public:
    QSqlDatabase db;
    struct PlcMemoryAddress{
        int base_address=4097;
        int other_signal=base_address+0;   //信号地址,M地址，PLC集中在一起另外配置
        int temp_signal=base_address+60;
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

    //温度信号组的成员数，从最大偏移值获取
    int getTempSignalValsNum();

    /** 除温度外的其它信号
     * @brief signalVals
     */
    QVector<Sensor*> signalVals;
    /**温度信号组
     * @brief tempSignalVals
     */
    QVector<Sensor*> tempSignalVals;
    void addSensor();


//    int getSignalReadCycle() const;

    int getRealTimeCurve_x_count() const ;
//    int getRecordCycle_s();

//    void setSignalReadCycle(int value);

    int getRealTimeCurve_time_s() const;
    void setRealTimeCurve_time_s(int value);




    ///刷新实时曲线周期
    /// \brief getFlashRealTimeCurve_s
    /// \return
    ///
    int getFlashRealTimeCurve_s() const;
    void setFlashRealTimeCurve_s(int value);



    int getRecordCycle_ms() const;
    void setRecordCycle_ms(int value);

signals:

private:

    int signalValsNum;
    //信号读取周期（ms）
    int recordCycle_ms;

    //实时曲线的x轴个数
    int realTimeCurve_x_count;

    //实时曲线的时长
    int realTimeCurve_time_s;

    //实时曲线刷新周期
    int flashRealTimeCurve_s;


};

#endif // DOWINIT_H
