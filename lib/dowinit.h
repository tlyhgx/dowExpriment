#ifndef DOWINIT_H
#define DOWINIT_H

#include <Para_with_plc.h>
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
        int base_holdingRegister_address=4096;
        int other_signal=base_holdingRegister_address+0;   //其它数字信号
        int temp_signal=base_holdingRegister_address+60;  //温度信号

        int para_to_plc=base_holdingRegister_address+408;  //参数起始地址
        int alarm=base_holdingRegister_address+9;  //报警
        int startCommand=base_holdingRegister_address+8; //启动指令
        int base_m_address=2048;   //M区首地址

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

    QList<Para_with_plc> getPara_with_plc();





    int getAskPlc_cycle_ms() const;
    void setAskPlc_cycle_ms(int value);

    int getRecord_cycle_s() const;
    void setRecord_cycle_s(int value);





signals:

private:

    int signalValsNum;
    //信号读取周期（ms）

    int record_cycle_s;
    //实时曲线的x轴个数
    int realTimeCurve_x_count;

    //实时曲线的时长
    int realTimeCurve_time_s;

    //实时曲线刷新周期
    int flashRealTimeCurve_s;

    //实时采样周期（ms）
    int askPlc_cycle_ms;

    QList<Para_with_plc> paras;

    void addPara_with_plc();

    void getPara();


};

#endif // DOWINIT_H
