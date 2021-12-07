#include "dowinit.h"

void DowInit::addSensor()
{
    //1.气体流量 2.气体压力 3.液体流量  4.转速  5~9.温度1  温度2。。。温度5
    Sensor *airFlow=new Sensor ("气体流量",0,0);
    Sensor *ariPress=new Sensor ("气体压力",0,1);
    Sensor *liquidFlow=new Sensor ("液体流量",0,2);
    Sensor *rotateSpeed=new Sensor ("搅拌转速",0,3);

    Sensor *tem1=new Sensor("1#温度",1,4);
    Sensor *tem2=new Sensor ("2#温度",1,5);
    Sensor *tem3=new Sensor ("3#温度",1,6);
    Sensor *tem4=new Sensor ("4#温度",1,7);
    Sensor *tem5=new Sensor ("5#温度",1,8);
    signalVals.append(airFlow);
    signalVals.append(ariPress);
    signalVals.append(liquidFlow);
    signalVals.append(rotateSpeed);
    signalVals.append(tem1);
    signalVals.append(tem2);
    signalVals.append(tem3);
    signalVals.append(tem4);
    signalVals.append(tem5);
}

int DowInit::getSignalReadCycle() const
{
    return signalReadCycle;
}

int DowInit::getRealTimeCurve_x_count() const
{
    return realTimeCurve_x_count;
}

void DowInit::setRealTimeCurve_x_count(int value)
{
    realTimeCurve_x_count = value;
}

DowInit::DowInit(QObject *parent) : QObject(parent)
{
    
    addSensor();
    signalReadCycle=500;
    realTimeCurve_x_count=3600;


}

int DowInit::getSignalValsNum()
{


    return signalVals.size();
}


