//
// Created by tangl on 2021-11-23.
//

#include <gtest/gtest.h>
#include <cmath>
#include "Sensor.h"
using namespace std;
class Test_sensor:public::testing::Test{
public:
    Sensor *temp1;

    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;
};

void Test_sensor::SetUp()
{
    temp1 = new Sensor("温度1",1,5);

}

void Test_sensor::TearDown()
{
}

//把从PLC的整型值改成需要的小数位
TEST_F(Test_sensor,2){

    int unTreatedVal=200;
    int decimalDigit=1;
    temp1->setUnTreatedVal(unTreatedVal);
    temp1->setDecimalDigit(decimalDigit);
    ASSERT_EQ(200*pow(0.1,decimalDigit),temp1->getValue());

}
//添加名称测试
TEST_F(Test_sensor,3)
{
    temp1->setName("温度1");
    ASSERT_EQ(temp1->getName(),"温度1");
}

//偏移地址
TEST_F(Test_sensor,4)
{
    temp1->setOffsetAddress(3);
    ASSERT_EQ(temp1->getOffsetAddress(),3);
}

//构造函数，带名称，小数位，偏移
TEST_F(Test_sensor,5)
{
    auto *sensor1=new Sensor ("传感器名称",3,5);

}

//获取小数位数
TEST_F(Test_sensor,decimalDigit)
{
    temp1->setDecimalDigit(1);
    ASSERT_EQ(temp1->getDecimalDigit(),1);
}
