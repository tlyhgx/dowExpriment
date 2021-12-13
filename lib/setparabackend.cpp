#include "setparabackend.h"


SetParaBackend::SetParaBackend(QObject *parent) : QObject(parent)
{
    connect(this,&SetParaBackend::recordCycle_sChanged,this,&SetParaBackend::recordRecycle_to_db);
}

void SetParaBackend::recordRecycle_to_db(int recordCycle_s)
{
    SysPara sysPara;
    sysPara.setRecordCycle_s_to_db(recordCycle_s);
}
