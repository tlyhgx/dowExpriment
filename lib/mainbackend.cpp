#include "mainbackend.h"
#include "oper.h"
#include "experiment.h"
#include <QDateTime>
#include <QTimer>
#include <math.h>
#include "getplcval.h"
#include "hwwutility.h"
#include "signal_vals.h"
//#pragma execution_character_set("utf-8")

MainBackend::MainBackend(DowInit *dowInit, GetPlcVal *getPlcVal, QObject *parent)
{
    this->dowInit=dowInit;
    this->getPlcVal=getPlcVal;


    connect(getPlcVal,&GetPlcVal::otherSignalValChanged,this,&MainBackend::sendOtherSignalVals_to_view);
    connect(getPlcVal,&GetPlcVal::tempSignalValChanged,this,&MainBackend::sendTempSignalVals_to_view);
    //把状态输出链接
    connect(getPlcVal,&GetPlcVal::outPutStateValChanged,this,&MainBackend::send_OutPutState_to_view);
    connect(this,&MainBackend::operNameChanged,this,&MainBackend::recordOperName_to_db);
    connect(this,&MainBackend::exprimentNameChanged,this,&MainBackend::recordExprimentName_to_db);
    connect(this,&MainBackend::makeInfo,this,&MainBackend::addInfoList);


    timer=new QTimer;
    connect(timer,&QTimer::timeout,this,&MainBackend::recVal_to_db);
    timer->start(dowInit->getRecord_cycle_s()*1000);

}

//void  MainBackend::askSignalVals()
//{

//    getPlcVal->askOtherSignalVals();
//}

void MainBackend::startSys()
{
    getPlcVal->startSys();
}

void MainBackend::stopSys()
{
    getPlcVal->stopSys();
}







void MainBackend::setInfoListModel(InfoListModel &infoListModel)
{
    m_infoListModel=&infoListModel;
}

void MainBackend::setAlarmsInfo(HwwAlarms &alarmsInfo)
{
    m_alarmsInfo=&alarmsInfo;
    connect(m_alarmsInfo,&HwwAlarms::makeAlarmInfo,this,&MainBackend::addInfoList);
}

void MainBackend::sendOtherSignalVals_to_view(QVariantList otherSignalVals)
{
    emit otherSignalValChanged(otherSignalVals);
}

void MainBackend::sendTempSignalVals_to_view(QVariantList tempSignalVals)
{
    emit tempSignalValChanged(tempSignalVals);
}

void MainBackend::send_OutPutState_to_view(QVariantList outPutStateVals)
{
    emit outPutStateChanged(outPutStateVals);
}

void MainBackend::addInfoList(QString info)
{

    QString curDateTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    InfoList infoList(curDateTime,info);
    m_infoListModel->addInfoList(infoList);
}






void MainBackend::recVal_to_db()
{


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
#include <time.h>       /* 调用时务必加上该头文件 */
// 自定义的一个延时函数delay()
void delay(int seconds) //  参数必须为整型，表示延时多少秒
{
    clock_t start = clock();
    clock_t lay = (clock_t)seconds * CLOCKS_PER_SEC;
    while ((clock()-start) < lay);
}

//TODO1:输出停止系统指令--读取系统运行状态--停--退出；--未停--输出系统停止
void MainBackend::eixtSys()
{


    int res=getPlcVal->getAlarms();
    vector<int>states= HwwUtility::int_vector_int_0_1(res);

    if(states[7]==0)
    {
        exit(0);
    }

    getPlcVal->ask_alarm_from_plc();

    delay(2);
    res=getPlcVal->getAlarms();
    states= HwwUtility::int_vector_int_0_1(res);
    if(states[7]==0)
    {
        exit(0);
    }else{
        getPlcVal->stopSys();
    }





}
