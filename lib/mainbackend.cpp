#include "mainbackend.h"
#include "oper.h"
#include "experiment.h"
#include <QDateTime>
#include <QTimer>
#include <math.h>
#include "signal_vals.h"
#pragma execution_character_set("utf-8")
MainBackend::MainBackend(DowInit *dowInit, MyModbus *mymodbus, QObject *parent)
{
    this->dowInit=dowInit;
    myModbus=mymodbus;


    connect(myModbus,&MyModbus::modbusReadReady,
            this,&MainBackend::getSignalVals);
    connect(this,&MainBackend::operNameChanged,this,&MainBackend::recordOperName_to_db);
    connect(this,&MainBackend::exprimentNameChanged,this,&MainBackend::recordExprimentName_to_db);
    connect(this,&MainBackend::makeInfo,this,&MainBackend::addInfoList);

    timer=new QTimer;
    connect(timer,&QTimer::timeout,this,&MainBackend::recVal_to_db);
    timer->start(dowInit->getRecordCycle_s()*1000);

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

void MainBackend::setInfoListModel(InfoListModel &infoListModel)
{
    m_infoListModel=&infoListModel;
}

void MainBackend::addInfoList(QString info)
{

    QString curDateTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    InfoList infoList(curDateTime,info);

    m_infoListModel->addInfoList(infoList);
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

void MainBackend::recVal_to_db()
{


    if(m_willRec){

        for(int i=0;i<signalVals.size();i++)
        {
            signal_vals.add_val_to_db(signalVals[i].toFloat(),QString::fromStdString(dowInit->signalVals[i]->getName()),id_experiment);
        }
    }


}

void MainBackend::recordOperName_to_db(QString operName)
{
    Oper oper;
    oper.addOneOper_to_db(operName);

}

void MainBackend::recordExprimentName_to_db(QString csExprimentName)
{

    Experiment expriment;
    Oper oper;
    int id_oper=oper.findLastOper_id_by_name_from_db(m_operName);
    expriment.addExpriment_to_db(csExprimentName,id_oper);

}
