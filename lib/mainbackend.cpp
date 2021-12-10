#include "mainbackend.h"
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

QString MainBackend::getOperName_from_db()
{
    return "测试人员1";
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
//    dowInit->
    //    QSqlDatabase db;
    //    if(!db.isOpen())
    //    {


    //        db=QSqlDatabase::addDatabase("QSQLITE");
    //        db.setHostName("localhost");      //设置数据库主机名
    //        db.setDatabaseName("dow_experiment_data.db");  //设置数据库名称
    //        db.setUserName("cjkj");         //设置用户名
    //        db.setPassword("cjkj5215");     //设置密码
    //        db.open();
    //    }
    //    QSqlQuery query;
}
