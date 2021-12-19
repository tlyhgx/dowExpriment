#include "setparabackend.h"

#pragma execution_character_set("utf-8")
void SetParaBackend::setRealTimeCurve_flashcycle_s(int realTimeCurve_flashcycle_s)
{

    if(m_realTimeCurve_flashcycle_s==realTimeCurve_flashcycle_s)
    {
        return;
    }
        m_realTimeCurve_flashcycle_s = realTimeCurve_flashcycle_s;
        emit realTimeCurve_flashcycle_sChanged(realTimeCurve_flashcycle_s);

}

void SetParaBackend::getParaFromPlc(QVariantList paraFromPlc)
{
    emit sendParaFromPlcToView(paraFromPlc);
}

SetParaBackend::SetParaBackend(QObject *parent) : QObject(parent)
{



}

SetParaBackend::SetParaBackend(DowInit *dowInit, GetPlcVal *getPlcVal, QObject *parent)
{
    this->dowInit=dowInit;
    this->getPlcVal=getPlcVal;
    connect(this,&SetParaBackend::recordCycle_sChanged,this,&SetParaBackend::recordRecycle_to_db);
    connect(this,&SetParaBackend::realTimeCurve_flashcycle_sChanged,this,&SetParaBackend::realTimeCurve_flashcycle_s_to_db);
    connect(this,&SetParaBackend::realTimeCurve_time_sChanged,this,&SetParaBackend::realTimeCurve_time_s_to_db);
    connect(this,&SetParaBackend::askPlc_cycle_msChanged,this,&SetParaBackend::askPlc_cycle_ms_to_db);
    connect(getPlcVal,&GetPlcVal::paraValsChanged,this,&SetParaBackend::getParaFromPlc);
    getPlcVal->askPara_from_plc(dowInit->plcMemoryAddress.para_to_plc,dowInit->getPara_with_plc());

}

QVariantList SetParaBackend::readPara()
{
    getPlcVal->askPara_from_plc(dowInit->plcMemoryAddress.para_to_plc,dowInit->getPara_with_plc());
    m_para_plc=getPlcVal->getParaVals();
    return m_para_plc;

}

void SetParaBackend::setPlcPara(QVariantList inputVal)
{
    QList<Para_with_plc> paras=dowInit->getPara_with_plc();
    for(int i=0;i<inputVal.size();i++)
    {
        paras[i].setGivenVal(inputVal[i].toFloat());
    }
    getPlcVal->setPara_to_plc(dowInit->plcMemoryAddress.para_to_plc,paras);
}



void SetParaBackend::recordRecycle_to_db(int recordCycle_s)
{
    sysPara.setRecordCycle_s_to_db(recordCycle_s);
}

void SetParaBackend::realTimeCurve_flashcycle_s_to_db(int realTimeCurve_flashcycle_s)
{
    sysPara.setRealTimeCureve_flashcycle_s_to_db(realTimeCurve_flashcycle_s);
}

void SetParaBackend::realTimeCurve_time_s_to_db(int realTimeCurve_time_s)
{
    sysPara.setRealTimeCurve_time_s_to_db(realTimeCurve_time_s);
}

void SetParaBackend::askPlc_cycle_ms_to_db(int askPlc_cycle_ms)
{
    sysPara.setAskPlc_cycle_ms_to_db(askPlc_cycle_ms);
}
