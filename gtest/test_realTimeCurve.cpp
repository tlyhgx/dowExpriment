

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
    GetPlcVal *getPlcVal=new GetPlcVal(dowInit,myModbus);
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
    backend=new RealTimeCurveBackend(dowInit,getPlcVal);

}

void Test_realTimeCurve::TearDown()
{
}


//周期赋值，并显示到界面
TEST_F(Test_realTimeCurve,emit_val_to_view){
    backend->emit_val_to_view();
}








//x_轴个数通过 数量=实时显示时长/刷新周期;
TEST_F(Test_realTimeCurve,x_num)
{
    dowInit->setRealTimeCurve_time_s(100);
    dowInit->setFlashRealTimeCurve_s(1);
    int time_s=dowInit->getRealTimeCurve_time_s();
    int readCycle=dowInit->getFlashRealTimeCurve_s();
    ASSERT_EQ(time_s/readCycle,dowInit->getRealTimeCurve_x_count());
    ASSERT_EQ(time_s/readCycle,backend->x_count());
}


#endif // TEST_REALTIMECURVE_H
