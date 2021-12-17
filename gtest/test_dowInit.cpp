#ifndef TEST_DOWINIT_H
#define TEST_DOWINIT_H



#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSqlQuery>
#include <para_with_plc.h>
using namespace testing;
#include "dowinit.h"
#pragma execution_character_set("utf-8")

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
    dowInit->plcMemoryAddress.other_signal=1028;
    ASSERT_EQ(dowInit->plcMemoryAddress.other_signal,1028);


}

//初始化modbus
TEST_F(TESTDowInit,3)
{

    dowInit->modbusSetting.portName="COM8";
    ASSERT_EQ(dowInit->modbusSetting.portName,"COM8");

}

//获取其它信号数
TEST_F(TESTDowInit,signalValsNum)
{
    ASSERT_EQ(dowInit->getSignalValsNum(),4);

}

//获取温度信号数
TEST_F(TESTDowInit,tempSignalValsNum){
    ASSERT_EQ(dowInit->getTempSignalValsNum(),5);
}
//添加其它信号组
TEST_F(TESTDowInit,signalVals)
{
    ASSERT_EQ(dowInit->signalVals[0]->getName(),"气体流量");
    ASSERT_EQ(dowInit->signalVals.size(),4);
}
//添加温度信号组
TEST_F(TESTDowInit,tempSignalVals)
{
    ASSERT_EQ(dowInit->tempSignalVals[0]->getName(),"1#温度");
    ASSERT_EQ(dowInit->tempSignalVals.size(),5);
}
//操作数据库
TEST_F(TESTDowInit,aboutdb){
    //    QSqlQuery query;
    //    bool res=query.exec("insert into alarm_para(id_alarm_para)"
    //                              " VALUES('2')");
    //    ASSERT_EQ(res,true);
}
//设置实时曲线刷新周期
TEST_F(TESTDowInit,flash){
    dowInit->setFlashRealTimeCurve_s(3);
    ASSERT_EQ(dowInit->getFlashRealTimeCurve_s(),3);
}
//实时曲线的个数
TEST_F(TESTDowInit,curve_x_count){
    dowInit->setRealTimeCurve_time_s(600);
    dowInit->setFlashRealTimeCurve_s(2);
    ASSERT_EQ(dowInit->getRealTimeCurve_x_count(),300);
    dowInit->setRealTimeCurve_time_s(430);
    dowInit->setFlashRealTimeCurve_s(1);
    ASSERT_EQ(dowInit->getRealTimeCurve_x_count(),430);
}
//实时曲线的时长
TEST_F(TESTDowInit,realTimeCurve_time){
    dowInit->setRealTimeCurve_time_s(650);
    ASSERT_EQ(dowInit->getRealTimeCurve_time_s(),650);
}
//设置信号读取周期
TEST_F(TESTDowInit,signalReadCycle)

{   dowInit->setAskPlc_cycle_ms(600);
    ASSERT_EQ(dowInit->getAskPlc_cycle_ms(),600) ;
}

//设置信号记录周期
TEST_F(TESTDowInit,record_cycle_s)

{   dowInit->setRecord_cycle_s(6);
    ASSERT_EQ(dowInit->getRecord_cycle_s(),6) ;
}
//添加plc内参数组
TEST_F(TESTDowInit,para_with_plc)
{

    QList<Para_with_plc>paras=dowInit->getPara_with_plc();
    ASSERT_EQ(paras.size(),8);

}
#endif // TEST_DOWINIT_H
