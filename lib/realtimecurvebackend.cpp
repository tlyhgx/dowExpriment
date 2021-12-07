#include "realtimecurvebackend.h"



RealTimeCurveBackend::RealTimeCurveBackend(DowInit *dowInit, MyModbus *mymodbus, QObject *parent)
{
    this->dowInit=dowInit;
    myModbus=mymodbus;
    connect(myModbus,&MyModbus::modbusReadReady,
            this,&RealTimeCurveBackend::getSignalVals);
}

QVariantList RealTimeCurveBackend::getSignalVals(QModbusDataUnit dataUnit)
{
    if(signalVals.isEmpty()){
        for(uint i=0;i<dataUnit.valueCount();i++)
        {
//            signalVals.pop_front();
            int decimalDigit=dowInit->signalVals[i]->getDecimalDigit();
            int val=dataUnit.values()[i];
            float res=(float)val*pow(0.1,decimalDigit);
            signalVals.append(res);
        }
       //添加x_count乘以signalValsNum个零
        for(int i=0;i<(dowInit->getRealTimeCurve_x_count()-1)*dowInit->getSignalValsNum();i++)
        {
            signalVals.append(0);
        }

    }else{
        //移除前端signalValsNum，添加后端signalValsNum

        for(uint i=0;i<dataUnit.valueCount();i++)
        {
            signalVals.pop_front();
            int decimalDigit=dowInit->signalVals[i]->getDecimalDigit();
            int val=dataUnit.values()[i];
            float res=(float)val*pow(0.1,decimalDigit);
            signalVals.append(res);
        }

    }


//TODO1
//    emit signalValChanged(signalVals);
    return signalVals;
}
