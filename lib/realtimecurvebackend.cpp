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
    QVariantList signalVals;
    signalVals<<getPlcVal->getSignalVals();
    signalVals<<getPlcVal->getTempSignalVals();
    emit signalValChanged(signalVals);

}
