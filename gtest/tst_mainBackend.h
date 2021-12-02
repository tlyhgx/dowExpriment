//#ifndef TST_MAINBACKEND_H
//#define TST_MAINBACKEND_H


//#include "mainbackend.h"

//#include <gtest/gtest.h>
//#include <gmock/gmock-matchers.h>
//#include <dowinit.h>
//#include "mymodbus.h"





//using namespace testing;
//using namespace std;

//class TestBackend : public ::testing::Test{
//public:

//    DowInit dowInit;
//    MyModbus myModbus;
//    MainBackend *mainBackend;
//protected:
//     void SetUp() {

//    mainBackend=new MainBackend(*dowInit,*myModbus);
//    }
//    void TearDown() {

//    }
//};






////调用modbus的读取功能，有私有变量modbus,关联
//TEST_F(TestBackend,2)
//{
//    MyModbus *myModbus=new MyModbus() ;
//    mainBackend.setMyModbus(myModbus);
//}
////调用dowInit的初始数据，关联
//TEST_F(TestBackend,3)
//{
//    DowInit *dowInit=new DowInit ();
//    mainBackend.setDowInit(dowInit);
//}



////要有个slot接收signalVals(),connect signals
//TEST_F(TestBackend,4)
//{
//    mainBackend.askSignalVals();

//    QVariantList signalVals;
//    QModbusDataUnit dataUnit;
//    signalVals=mainBackend.getSignalVals(dataUnit);
//    //返回值数量=dowInit中的nums
//    ASSERT_EQ(signalVals.size(),dowInit.plcMemoryAddress.signalNum);

//}

////要有个返回给界面的函数
//TEST_F(TestBackend,5)
//{
//    QVariantList signalVals;

//    signalVals=mainBackend.retSignalVals();

//}


//#endif // TST_MAINBACKEND_H

