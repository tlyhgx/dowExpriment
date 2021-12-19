
#ifndef TEST_PARA_WITH_PLC_H
#define TEST_PARA_WITH_PLC_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <getplcval.h>
#include <para_with_plc.h>
using namespace testing;

//参数温度1高位报警值
TEST(Test_para_with_plc,temp1){
    Para_with_plc paraTemp1("温度1高位报警",TreatmentMethod::x10,110);
    ASSERT_EQ(paraTemp1.getResVal_DWORD()[0],1100);
    ASSERT_EQ(paraTemp1.getResVal_DWORD()[1],0);
    Para_with_plc paraTemp2("温度2高位报警",TreatmentMethod::x10,120);
    ASSERT_EQ(paraTemp2.getResVal_DWORD()[0],1200);
    ASSERT_EQ(paraTemp2.getResVal_DWORD()[1],0);
}

//参数液体流量最小值
TEST(Test_para_with_plc,flow){
    float input_val=32.5;
    Para_with_plc paraFlow("液体流量报警低位",TreatmentMethod::to_float,input_val);
    ASSERT_EQ(paraFlow.getResVal_DWORD()[0],GetPlcVal::parseFloat2Int(input_val)[0]);
    ASSERT_EQ(paraFlow.getResVal_DWORD()[1],GetPlcVal::parseFloat2Int(input_val)[1]);

    input_val=32505566;
        Para_with_plc paraFlow1("液体流量报警低位",TreatmentMethod::to_float,input_val);
        ASSERT_EQ(paraFlow1.getResVal_DWORD()[0],GetPlcVal::parseFloat2Int(input_val)[0]);
        ASSERT_EQ(paraFlow1.getResVal_DWORD()[1],GetPlcVal::parseFloat2Int(input_val)[1]);
}

//更改参数值
TEST(Test_para_with_plc,changePara){
    float input_val=32.5;
    Para_with_plc paraFlow("液体流量报警低位",TreatmentMethod::to_float,20.3);
    paraFlow.setGivenVal(input_val);
    ASSERT_EQ(input_val,paraFlow.getGivenVal());
}
#endif
