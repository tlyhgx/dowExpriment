#include "realtimecurvebackend.h"

#pragma execution_character_set("utf-8")

RealTimeCurveBackend::RealTimeCurveBackend(DowInit *dowInit,GetPlcVal *getPlcVal, QObject *parent)
{
    this->dowInit=dowInit;
    this->getPlcVal=getPlcVal;

    timer_realTimeCurve=new QTimer;
    connect(timer_realTimeCurve,&QTimer::timeout,this,&RealTimeCurveBackend::emit_val_to_view);
    timer_realTimeCurve->start(dowInit->getFlashRealTimeCurve_s()*1000);



}

int RealTimeCurveBackend::x_count()
{
    return dowInit->getRealTimeCurve_x_count();
}



void RealTimeCurveBackend::emit_val_to_view()
{
    otherSignalVals=getPlcVal->getSignalVals();
    tempSignalVals=getPlcVal->getTempSignalVals();
    signalVals.clear();
    for(int i=0;i<otherSignalVals.size();i++)
    {
        signalVals<<otherSignalVals[i].toFloat();
    }
    for(int i=0;i<tempSignalVals.size();i++)
    {
        signalVals<<tempSignalVals[i].toFloat();
    }

    if(signalVals.size()>0){
        emit signalValChanged(signalVals);
    }


}
