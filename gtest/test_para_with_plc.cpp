
#ifndef TEST_PARA_WITH_PLC_H
#define TEST_PARA_WITH_PLC_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <getplcval.h>
#include <para_with_plc.h>
using namespace testing;

//�����¶�1��λ����ֵ
TEST(Test_para_with_plc,temp1){
    Para_with_plc paraTemp1("�¶�1��λ����",TreatmentMethod::x10,110);
    ASSERT_EQ(paraTemp1.getResVal_DWORD()[0],1100);
    ASSERT_EQ(paraTemp1.getResVal_DWORD()[1],0);
    Para_with_plc paraTemp2("�¶�2��λ����",TreatmentMethod::x10,120);
    ASSERT_EQ(paraTemp2.getResVal_DWORD()[0],1200);
    ASSERT_EQ(paraTemp2.getResVal_DWORD()[1],0);
}

//����Һ��������Сֵ
TEST(Test_para_with_plc,flow){
    float input_val=32.5;
    Para_with_plc paraFlow("Һ������������λ",TreatmentMethod::to_float,input_val);
    ASSERT_EQ(paraFlow.getResVal_DWORD()[0],GetPlcVal::parseFloat2Int(input_val)[0]);
    ASSERT_EQ(paraFlow.getResVal_DWORD()[1],GetPlcVal::parseFloat2Int(input_val)[1]);

    input_val=32505566;
        Para_with_plc paraFlow1("Һ������������λ",TreatmentMethod::to_float,input_val);
        ASSERT_EQ(paraFlow1.getResVal_DWORD()[0],GetPlcVal::parseFloat2Int(input_val)[0]);
        ASSERT_EQ(paraFlow1.getResVal_DWORD()[1],GetPlcVal::parseFloat2Int(input_val)[1]);
}

//���Ĳ���ֵ
TEST(Test_para_with_plc,changePara){
    float input_val=32.5;
    Para_with_plc paraFlow("Һ������������λ",TreatmentMethod::to_float,20.3);
    paraFlow.setGivenVal(input_val);
    ASSERT_EQ(input_val,paraFlow.getGivenVal());
}
#endif
