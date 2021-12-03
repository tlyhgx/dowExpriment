#include "getplcval.h"



GetPlcVal::GetPlcVal(DowInit *dowInit, MyModbus *mymodbus, QObject *parent)
{
    this->dowInit=dowInit;
    myModbus=mymodbus;

    QTimer *timer500=new QTimer;
    connect(timer500,&QTimer::timeout,this,&GetPlcVal::askSignalVals);
    timer500->start(dowInit->getSignalReadCycle());
}

void GetPlcVal::askSignalVals()
{
    myModbus->modbusRead(1,QModbusDataUnit::HoldingRegisters,
                         dowInit->plcMemoryAddress.signal,dowInit->getSignalValsNum());

}
