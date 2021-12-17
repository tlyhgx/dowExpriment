#include "mainbackend.h"
#include "oper.h"
#include "experiment.h"
#include <QDateTime>
#include <QTimer>
#include <math.h>
#include "getplcval.h"
#include "signal_vals.h"
#pragma execution_character_set("utf-8")

MainBackend::MainBackend(DowInit *dowInit, GetPlcVal *getPlcVal, QObject *parent)
{
    this->dowInit=dowInit;
    this->getPlcVal=getPlcVal;


    connect(getPlcVal,&GetPlcVal::otherSignalValChanged,this,&MainBackend::sendOtherSignalVals_to_view);
    connect(getPlcVal,&GetPlcVal::tempSignalValChanged,this,&MainBackend::sendTempSignalVals_to_view);
    connect(this,&MainBackend::operNameChanged,this,&MainBackend::recordOperName_to_db);
    connect(this,&MainBackend::exprimentNameChanged,this,&MainBackend::recordExprimentName_to_db);
    connect(this,&MainBackend::makeInfo,this,&MainBackend::addInfoList);

    timer=new QTimer;
    connect(timer,&QTimer::timeout,this,&MainBackend::recVal_to_db);
    timer->start(dowInit->getRecord_cycle_s()*1000);

}

void  MainBackend::askSignalVals()
{

    getPlcVal->askOtherSignalVals();
}







void MainBackend::setInfoListModel(InfoListModel &infoListModel)
{
    m_infoListModel=&infoListModel;
}

void MainBackend::sendOtherSignalVals_to_view(QVariantList otherSignalVals)
{
    emit otherSignalValChanged(otherSignalVals);
}

void MainBackend::sendTempSignalVals_to_view(QVariantList tempSignalVals)
{
    emit tempSignalValChanged(tempSignalVals);
}

void MainBackend::addInfoList(QString info)
{

    QString curDateTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    InfoList infoList(curDateTime,info);

    m_infoListModel->addInfoList(infoList);
}





void MainBackend::recVal_to_db()
{

    //TODO1:
    if(m_willRec){

        otherSignalVals=getPlcVal->getSignalVals();
        tempSignalVals=getPlcVal->getTempSignalVals();
        for(int i=0;i<otherSignalVals.size();i++)
        {
            signal_vals.add_val_to_db(otherSignalVals[i].toFloat(),QString::fromStdString(dowInit->signalVals[i]->getName()),id_experiment);
        }
        for(int i=0;i<tempSignalVals.size();i++)
        {
            signal_vals.add_val_to_db(tempSignalVals[i].toFloat(),QString::fromStdString(dowInit->tempSignalVals[i]->getName()),id_experiment);
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
