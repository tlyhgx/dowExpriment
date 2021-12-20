
#ifndef TEST_GETPLCVAL_H
#define TEST_GETPLCVAL_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <para_with_plc.h>
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
//要求提供报警信息
TEST_F(Test_getPLCval,alarms)
{
    getPlcVal->ask_alarm_from_plc();
};
//获取报警值
TEST_F(Test_getPLCval,alarmVal){
    getPlcVal->getAlarms();
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
//浮点数 转 2个字
TEST_F(Test_getPLCval,float_to_dword)
{
    float a=1.234;
    vector<int16_t> res_dword=GetPlcVal::parseFloat2Int(a);
    float res=GetPlcVal::parseInt2Float(res_dword[1],res_dword[0]);
    ASSERT_EQ(int(a*100)/100,int(res*100)/100);

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

//读写温度1高位报警参数_PLC
TEST_F(Test_getPLCval,set_para_to_plc)
{
    //从指定位置设置数据，然后读取，做比对
    //实例化参数--成组--设置到PLC--读取--取值与原组中参数对比
    Para_with_plc paraTemp1("温度1高位报警",TreatmentMethod::x10,110);
//    Para_with_plc paraTemp2("温度2高位报警",TreatmentMethod::x10,70);
//    Para_with_plc paraLiquidFlow("流量",TreatmentMethod::to_float,33.5);
    QList<Para_with_plc> paras;
    paras<<paraTemp1;
    //    paras<<paraTemp1<<paraTemp2<<paraLiquidFlow;
    getPlcVal->setPara_to_plc(dowInit.plcMemoryAddress.para_to_plc,paras);
    getPlcVal->askPara_from_plc(dowInit.plcMemoryAddress.para_to_plc,paras);
//    _sleep(500);

//    ASSERT_EQ(ret[5].toFloat(),5.0f);
}




#endif // TEST_GETPLCVAL_H
