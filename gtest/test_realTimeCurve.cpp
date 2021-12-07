

#ifndef TEST_REALTIMECURVE_H
#define TEST_REALTIMECURVE_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <dowinit.h>
#include <mymodbus.h>
#include "realtimecurvebackend.h"
#include <ctime>
using namespace testing;


class Test_realTimeCurve:public ::testing::Test{
public:
    RealTimeCurveBackend *backend;
    DowInit *dowInit=new DowInit;
    MyModbus *myModbus=new MyModbus;
    QVector<quint16> retVal;
    QVector<float> retVal_addDicemal;
    int signalValsNum=dowInit->getSignalValsNum();

    // Test interface
    void getSignalVal();

protected:
    void SetUp() override;
    void TearDown() override;
};

void Test_realTimeCurve::getSignalVal()
{
    retVal.clear();
    retVal_addDicemal.clear();
    for(int i=0;i<dowInit->getSignalValsNum();i++)
    {
        srand(time(NULL));
        int n = qrand() % 100;
        retVal.append(n);
    }

    for(int i=0;i<retVal.size();i++)
    {
        int decimalDigit=dowInit->signalVals[i]->getDecimalDigit();
        int val=retVal[i];
        float res=(float)val*pow(0.1,decimalDigit);
        retVal_addDicemal.append(res);
    }
}

void Test_realTimeCurve::SetUp()
{
    backend=new RealTimeCurveBackend(dowInit,myModbus);




}

void Test_realTimeCurve::TearDown()
{
}




//获取实时温度值，第一组；收到modbusReadReady，存储到signalVals
//要输出的是  温度1 温度2。。。。温度1  温度2。。。 温度1 温度2 。。。
TEST_F(Test_realTimeCurve,signalVals){

    getSignalVal();
    QModbusDataUnit dataUint(QModbusDataUnit::HoldingRegisters,
                             dowInit->plcMemoryAddress.signal,retVal);
    QVariantList signalVals=backend->getSignalVals(dataUint);
    ASSERT_EQ(signalVals[0],retVal_addDicemal[0]);
    ASSERT_EQ(signalVals[1],retVal_addDicemal[1]);
    ASSERT_EQ(signalVals[5],retVal_addDicemal[5]);
//    ASSERT_EQ(signalVals.size(),x_count*);
}



//signalVals的大小,与显示的横坐标个数n有关
//最多有n个数据
TEST_F(Test_realTimeCurve,signalVal_nums)
{
    int x_count=2;

    dowInit->setRealTimeCurve_x_count(x_count);
    getSignalVal();
    QModbusDataUnit *dataUint=new QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                             dowInit->plcMemoryAddress.signal,retVal);
    getSignalVal();
    dataUint->setValues(retVal);
    getSignalVal();
    dataUint->setValues(retVal);

    QVariantList signalVals=backend->getSignalVals(*dataUint);
    ASSERT_EQ(signalVals.size(),x_count*signalValsNum);
}


//TODO:获取实时温度的同步时间组



#endif // TEST_REALTIMECURVE_H
