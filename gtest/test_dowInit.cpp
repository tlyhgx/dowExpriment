﻿#ifndef TEST_DOWINIT_H
#define TEST_DOWINIT_H



#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
using namespace testing;
#include "dowinit.h"

class TESTDowInit:public ::testing::Test{
public: DowInit *dowInit;



    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;

private:
    void TestBody() override;
};

void TESTDowInit::SetUp()
{
    dowInit=new DowInit;
}

void TESTDowInit::TearDown()
{
}

void TESTDowInit::TestBody()
{
}


//设置modbus读取信号值的地址
TEST_F(TESTDowInit,1)
{

//    ASSERT_EQ(dowInit->plcMemoryAddress.signal,4097);
    dowInit->plcMemoryAddress.signal=1028;
   ASSERT_EQ(dowInit->plcMemoryAddress.signal,1028);


}

//初始化modbus
TEST_F(TESTDowInit,3)
{

    dowInit->modbusSetting.portName="COM8";
    ASSERT_EQ(dowInit->modbusSetting.portName,"COM8");

}

//获取信号数
TEST_F(TESTDowInit,signalValsNum)
{
    ASSERT_EQ(dowInit->getSignalValsNum(),9);

}

//添加信号组
TEST_F(TESTDowInit,signalVals)
{
      ASSERT_EQ(dowInit->signalVals[0]->getName(),"气体流量");
    ASSERT_EQ(dowInit->signalVals.size(),9);
}

//设置信号读取周期
TEST_F(TESTDowInit,signalReadCycle)
{
    ASSERT_EQ(dowInit->getSignalReadCycle(),500) ;
}

//设置实时曲线图的x轴个数
TEST_F(TESTDowInit,x_count)
{
    ASSERT_EQ(dowInit->getRealTimeCurve_x_count(),3600);
}
#endif // TEST_DOWINIT_H
