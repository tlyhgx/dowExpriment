﻿#ifndef MYMODBUS_H
#define MYMODBUS_H

#include <QModbusClient>
#include <QObject>
#include <QSerialPort>
#include<QDebug>

class MyModbus:public QObject
{
    Q_OBJECT
public:
    MyModbus();
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


        QString portName="COM7";
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;

        int responseTime = 1000;
        int numberOfRetries = 3;

    };


private:

    Settings m_settings;
};

#endif // MYMODBUS_H