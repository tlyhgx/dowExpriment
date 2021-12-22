#ifndef TEST_OUTPUT_STATE_H
#define TEST_OUTPUT_STATE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <outputstate.h>
//����outPutState��--������--��״̬
TEST(Test_out_put_state,1)
{
    OutPutState outPutState("����������",true);
    ASSERT_EQ(outPutState.outPutName(),"����������");
    ASSERT_EQ(outPutState.state(),true);

}

//����outPutStates��--�����outPutState--�鿴������
TEST(Test_out_put_states,1){
    OutPutStates outPutStates;
    OutPutState outPutState("����������",true);
    OutPutState outPutState1("�䶯�ù���",true);
    OutPutState outPutState2("���蹤��",false);
    outPutStates.add(outPutState);
    outPutStates.add(outPutState1);
    outPutStates.add(outPutState2);
    ASSERT_EQ(outPutStates.member().size(),3);

}

#endif
