#ifndef TST_MAINBACKEND_H
#define TST_MAINBACKEND_H


#include "mainbackend.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <dowinit.h>
#include "mymodbus.h"





using namespace testing;
using namespace std;

class TestBackend : public ::testing::Test{
public:

    DowInit *dowInit=new DowInit;
    MyModbus *myModbus=new MyModbus;
//    MainBackend xx(dowInit,myModbus);
    MainBackend *mainBackend;
protected:
     void SetUp() {

    mainBackend=new MainBackend(dowInit,myModbus);
    }
    void TearDown() {
        delete mainBackend;
        delete dowInit;
        delete myModbus;
    }
};






//调用modbus的读取功能，有私有变量modbus,关联
TEST_F(TestBackend,2)
{
    MyModbus *myModbus=new MyModbus() ;
    mainBackend->setMyModbus(myModbus);
}
//调用dowInit的初始数据，关联
TEST_F(TestBackend,3)
{
    DowInit *dowInit=new DowInit ();
    mainBackend->setDowInit(dowInit);
}



//要有个slot接收signalVals(),connect signals
//TEST_F(TestBackend,4)
//{
//    mainBackend->askSignalVals();

//    QVariantList signalVals;
//    QModbusDataUnit dataUnit;
//        _sleep(1000);
//    signalVals=mainBackend->getSignalVals(dataUnit);


//    //返回值数量=dowInit中的nums
//    EXPECT_EQ(signalVals.size(),dowInit->plcMemoryAddress.signalNum);

//}

//获取传递给界面的值
TEST_F(TestBackend,5)
{
    QVariantList signalVals;

    signalVals=mainBackend->retSignalVals();

}


//从PLC读取的信号量，分配给数组并输出
//1.气体流量 2.气体压力 3.液体流量  4.转速  5~9.温度1  温度2。。。温度5
TEST_F(TestBackend,6)
{
    QVector<quint16> retVal;
    for(int i=0;i<dowInit->getSignalValsNum();i++)
    {
        retVal.append(i);
    }
    QModbusDataUnit dataUint(QModbusDataUnit::HoldingRegisters,
                             dowInit->plcMemoryAddress.signal,retVal);
    QVariantList signalVals=mainBackend->getSignalVals(dataUint);
    ASSERT_EQ(signalVals[0],0);
    ASSERT_EQ(signalVals[1],1);

    ASSERT_EQ(signalVals[5],0.5);

}

#endif // TST_MAINBACKEND_H

