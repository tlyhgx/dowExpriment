#ifndef TST_PARABACKEND_H
#define TST_PARABACKEND_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <setparabackend.h>
#include <syspara.h>


class Test_setParaBackend:public ::testing::Test{
public:
    SetParaBackend setParaBackend;
    SysPara sysPara;

    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;
};

void Test_setParaBackend::SetUp()
{
}

void Test_setParaBackend::TearDown()
{
}


//添加界面设置和读取 数据记录周期的
TEST_F(Test_setParaBackend,1){
    //属性--读、写--recordCycle_s
    int recordCycle_s=5;
    setParaBackend.setRecordRecycle_s(recordCycle_s);
    int ret=setParaBackend.recordRecycle_s();
    ASSERT_EQ(recordCycle_s,ret);
}

//数据记录周期写入数据库
TEST_F(Test_setParaBackend,2){
    //界面设置后，数据改变，触发写入数据库动作
    int recordCycle_s=20;
    setParaBackend.setRecordRecycle_s(recordCycle_s);
    //从数据库读取后比对
    SysPara sysPara;
    int ret=sysPara.getRecordRecycle_s_from_db();
    ASSERT_EQ(ret,recordCycle_s);

    recordCycle_s=15;
    setParaBackend.setRecordRecycle_s(recordCycle_s);
    ret=sysPara.getRecordRecycle_s_from_db();
    ASSERT_EQ(ret,recordCycle_s);
}
////参数设置界面要从PLC读取参数———温度1高位报警
//TEST_F(Test_setParaBackend,readFromPlc)
//{
//    int tem1_alam_para_with_plc=120;
//    sysPara.setTem1_alam_para_with_plc(tem1_alam_para_with_plc);
//    int ret=sysPara.getTem1_alam_para_with_plc();
//    ASSERT_EQ(tem1_alam_para_with_plc,ret/10);
//}

//TODO:数据记录周期，假如小于1s，或大于3000s,默认改为5S


#endif

