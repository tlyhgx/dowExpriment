
#ifndef TEST_HWWUTILITY_H
#define TEST_HWWUTILITY_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <hwwutility.h>
#include <vector>
using namespace std;
//通过异或获取变化位数组
TEST(Test_utility,xor){
    int input_one=0;
    int input_two=3;
    vector<int> res= HwwUtility::xor_get_diff(input_one,input_two);
    ASSERT_EQ(res[0],1);
    ASSERT_EQ(res[1],1);
    ASSERT_EQ(res[2],0);
}
//int-->32bit vector<int>
TEST(Test_utility,int_vector)
{
    int givenVal=4;
    vector<int> res=HwwUtility::int_vector_int_0_1(givenVal);
    ASSERT_EQ(res[0],0);
    ASSERT_EQ(res[1],0);
    ASSERT_EQ(res[2],1);

    givenVal=5;
    res=HwwUtility::int_vector_int_0_1(givenVal);
    ASSERT_EQ(res[0],1);
    ASSERT_EQ(res[1],0);
    ASSERT_EQ(res[2],1);
    ASSERT_EQ(res[3],0);


}
#endif
