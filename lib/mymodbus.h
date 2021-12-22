#ifndef MYMODBUS_H
#define MYMODBUS_H

#include <QModbusClient>
#include <QObject>
#include <QSerialPort>
#include<QDebug>
#include "dowinit.h"

class MyModbus:public QObject
{
    Q_OBJECT
public:
    MyModbus();
    MyModbus(const DowInit &dowInit);
    ~MyModbus();
    QModbusClient *modbusDevice=nullptr;


    void modbusDisconnect(void);
    void modbusRead(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries);
    void modbusReadData(void);
    void modbusWrite(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries, QVector<quint16> data);
    void modbusWrite_twoBytes(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries, QVector<quint16> data);


private:
    void modbusConnect(void);



    void modbusMessage(void);
    void modbusMessage(QString mess);

signals:
    void modbusReadReady(QModbusDataUnit dataUnit);
public:

    struct Settings {


        QString portName="COM1";
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;

        int responseTime = 500;
        int numberOfRetries = 1;

    };



public:

    Settings m_settings;
    void setParFromInit(DowInit dowInit);
};

#endif // MYMODBUS_H
