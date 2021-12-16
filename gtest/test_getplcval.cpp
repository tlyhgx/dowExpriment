
#ifndef TEST_GETPLCVAL_H
#define TEST_GETPLCVAL_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "getplcval.h"
using namespace testing;

class Test_getPLCval:public ::testing::Test{
  public:
    DowInit dowInit;
    MyModbus myModbus;
    GetPlcVal* getPlcVal;
    // Test interface
protected:
    void SetUp() override;
};

void Test_getPLCval::SetUp()
{
    getPlcVal=new GetPlcVal(&dowInit,&myModbus);
}


TEST_F(Test_getPLCval,1)
{

    getPlcVal->askOtherSignalVals();
}

//2个字 转浮点
TEST_F(Test_getPLCval,changt_to_float)
{
    int x1=14969;
    int x2=62470;
    float res=GetPlcVal::parseInt2Float(x1,x2);
    ASSERT_TRUE(0.0f<res&&res<1.0f);
//    ASSERT_EQ(res,0.000953496);
}

//把其它地方的采集信号放到getPlcval类中
//处理其它信号
TEST_F(Test_getPLCval,getSignalVals){

    QVector<quint16> retVal;

    int x1=14969;
    int x2=62470;

    for(int i=0;i<dowInit.getSignalValsNum()*2;i++)
    {
        if(i%2){
            retVal.append(x1);
        }else{
            retVal.append(x2);
        }

    }
    ASSERT_EQ(retVal.size(),8);
    QModbusDataUnit dataUint(QModbusDataUnit::HoldingRegisters,
                             dowInit.plcMemoryAddress.other_signal,retVal);
    getPlcVal->recieveReply(dataUint);
    ASSERT_EQ(getPlcVal->getSignalVals().count(),4);
    ASSERT_TRUE(getPlcVal->getSignalVals()[0].toFloat()>0&&getPlcVal->getSignalVals()[0].toFloat()<1);

}
//处理温度信号
TEST_F(Test_getPLCval,getTempSignalVals){
    //给温度随机赋值--getTempSignalVals--QVariantList 有一个小数

    QVector<quint16> retVal;
    for(int i=0;i<dowInit.getTempSignalValsNum();i++)
    {
        retVal<<(rand()%(2000)+1);
    }
    ASSERT_TRUE(retVal[0]>0&&retVal[0]<2000);
    ASSERT_EQ(retVal.size(),5);
    QModbusDataUnit dataUint(QModbusDataUnit::HoldingRegisters,
                             dowInit.plcMemoryAddress.temp_signal,retVal);
    getPlcVal->recieveReply(dataUint);
    ASSERT_EQ(getPlcVal->getTempSignalVals().count(),5);
    ASSERT_EQ(int(getPlcVal->getTempSignalVals()[0].toFloat()*10),retVal[0]);

}

#endif // TEST_GETPLCVAL_H
