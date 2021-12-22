#ifndef TEST_OUTPUT_STATE_H
#define TEST_OUTPUT_STATE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <outputstate.h>
//创建outPutState类--有名字--有状态
TEST(Test_out_put_state,1)
{
    OutPutState outPutState("加热器工作",true);
    ASSERT_EQ(outPutState.outPutName(),"加热器工作");
    ASSERT_EQ(outPutState.state(),true);

}

//创建outPutStates类--可添加outPutState--查看组内容
TEST(Test_out_put_states,1){
    OutPutStates outPutStates;
    OutPutState outPutState("加热器工作",true);
    OutPutState outPutState1("蠕动泵工作",true);
    OutPutState outPutState2("搅拌工作",false);
    outPutStates.add(outPutState);
    outPutStates.add(outPutState1);
    outPutStates.add(outPutState2);
    ASSERT_EQ(outPutStates.member().size(),3);

}

#endif
