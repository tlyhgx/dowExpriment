#ifndef TEST_DOWINIT_H
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

    ASSERT_EQ(dowInit->plcMemoryAddress.signal,2060);
    dowInit->plcMemoryAddress.signal=1028;
   ASSERT_EQ(dowInit->plcMemoryAddress.signal,1028);


}
//设置modbus读取信号值的地址
TEST_F(TESTDowInit,2)
{

    ASSERT_EQ(dowInit->plcMemoryAddress.signalNum,8);
    dowInit->plcMemoryAddress.signalNum=10;
   ASSERT_EQ(dowInit->plcMemoryAddress.signalNum,10);


}
//初始化modbus
TEST_F(TESTDowInit,3)
{
    ASSERT_EQ(dowInit->modbusSetting.portName,"COM1");
    dowInit->modbusSetting.portName="COM8";
    ASSERT_EQ(dowInit->modbusSetting.portName,"COM8");

}


#endif // TEST_DOWINIT_H
