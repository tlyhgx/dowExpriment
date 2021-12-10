﻿#include "mainbackend.h"
#include "oper.h"
#include <math.h>


MainBackend::MainBackend(DowInit *dowInit, MyModbus *mymodbus, QObject *parent)
{
    this->dowInit=dowInit;
    myModbus=mymodbus;


    connect(myModbus,&MyModbus::modbusReadReady,
            this,&MainBackend::getSignalVals);
    connect(this,&MainBackend::operNameChanged,this,&MainBackend::recordOperName_to_db);
}

void  MainBackend::askSignalVals()
{
    myModbus->modbusRead(1,QModbusDataUnit::HoldingRegisters,
                         dowInit->plcMemoryAddress.signal,dowInit->getSignalValsNum());

}

QVariantList MainBackend::retSignalVals()
{
    return signalVals;
}

void MainBackend::setMyModbus(MyModbus *value)
{
    myModbus = value;
}

void MainBackend::setDowInit(DowInit *value)
{
    dowInit = value;
}



QVariantList MainBackend::getSignalVals(QModbusDataUnit dataUnit)
{

    signalVals.clear();
    for(uint i=0;i<dataUnit.valueCount();i++)
    {
        int decimalDigit=dowInit->signalVals[i]->getDecimalDigit();
        int val=dataUnit.values()[i];
        float res=(float)val*pow(0.1,decimalDigit);
        signalVals.append(res);
    }

    emit signalValChanged(signalVals);
    return signalVals;
}

void MainBackend::recordOperName_to_db(QString operName)
{
    Oper oper;
    oper.addOneOper_to_db(operName);

}
