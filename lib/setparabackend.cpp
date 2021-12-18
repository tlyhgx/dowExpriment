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
//    sysPara.setRealTimeCureve_flashcycle_s_to_db(realTimeCurve_flashcycle_s);
}

SetParaBackend::SetParaBackend(QObject *parent) : QObject(parent)
{
    connect(this,&SetParaBackend::recordCycle_sChanged,this,&SetParaBackend::recordRecycle_to_db);
    connect(this,&SetParaBackend::realTimeCurve_flashcycle_sChanged,this,&SetParaBackend::realTimeCurve_flashcycle_s_to_db);
    connect(this,&SetParaBackend::realTimeCurve_time_sChanged,this,&SetParaBackend::realTimeCurve_time_s_to_db);
    connect(this,&SetParaBackend::askPlc_cycle_msChanged,this,&SetParaBackend::askPlc_cycle_ms_to_db);
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
