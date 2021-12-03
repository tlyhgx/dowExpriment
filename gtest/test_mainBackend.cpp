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

//要有个返回给界面的函数
TEST_F(TestBackend,5)
{
    QVariantList signalVals;

    signalVals=mainBackend->retSignalVals();

}


//从PLC读取的信号量，分配给数组并输出
//1.气体流量 2.气体压力 3.液体流量  4.转速  5~9.温度1  温度2。。。温度5
//TODO1:
TEST_F(TestBackend,6)
{
//    const QVector<quint16> retVal;
//    for(int i=0;i<dowInit->signalNum;i++)
//    {

//    }
//    QModbusDataUnit dataUint(QModbusDataUnit::HoldingRegisters,)
}

#endif // TST_MAINBACKEND_H

