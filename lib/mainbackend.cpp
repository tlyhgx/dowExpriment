#include "mainbackend.h"

MainBackend::MainBackend(QObject *parent) : QObject(parent)
{

}

QVariantList  MainBackend::askSignalVals()
{
    QVariantList  signalVals;
//    myModbus->modbusRead(1,QModbusDataUnit::HoldingRegisters,
//                         dowInit->plcMemoryAddress.signal,dowInit->plcMemoryAddress.signalNum);

    signalVals<<1.02;
    return signalVals;

}

void MainBackend::setMyModbus(My_Modbus *value)
{
    myModbus = value;
}

void MainBackend::setDowInit(DowInit *value)
{
    dowInit = value;
}
