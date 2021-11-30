//
// Created by tangl on 2021-11-19.
//

#ifndef HWWIOMODULE_MY_MODBUS_H
#define HWWIOMODULE_MY_MODBUS_H

#include <QObject>
#include <QSerialPort>
#include <QModbusDataUnit>
#include <QModbusRtuSerialMaster>
using namespace std;
class My_Modbus:public QObject {
Q_OBJECT
public:
    My_Modbus();
    ~My_Modbus() ;

    void modbusConnect();

    void modbusDisconnect();  //todo2:在PLC中要处理
    void modbusRead(int serverAddress,QModbusDataUnit::RegisterType table,int startAddress,int numOfEntries);
    void modbusWrite(int serverAddress,QModbusDataUnit::RegisterType table,int startAddress,int numOfEntries,QVector<quint16> data);

    string modbusInfo;
signals:
    void modbusReadReady(QModbusDataUnit dataUnit);

public slots:

    void modbusStateChanged(int state);

    void modbusReadData(void);

    void modbusMessage(void);

    void modbusMessage(QString mess);

public:
    struct Settings{
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;
        QString portName="COM5";//串口号，默认为com5;可设置为com1,com2...
        int responseTime = 1000;
        int numOfRetries=3;
    };
    Settings m_settings;
    private:
    QModbusClient *modbusDevice=nullptr;





};


#endif //HWWIOMODULE_MY_MODBUS_H
