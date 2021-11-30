#ifndef TST_MAINBACKEND_H
#define TST_MAINBACKEND_H


#include "mainbackend.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <dowinit.h>
#include "My_Modbus.h"





using namespace testing;
using namespace std;

class TestBackend : public ::testing::Test{
public:
    MainBackend mainBackend;
protected:
     void SetUp() {

    }
    void TearDown() {

    }
};


//有一个askSignalVals数组
TEST_F(TestBackend,1)
{

    QVariantList signalVals;
    signalVals=mainBackend.askSignalVals();
    ASSERT_EQ(signalVals.size(),1);
}
//调用modbus的读取功能，有私有变量modbus,关联
TEST_F(TestBackend,2)
{
    My_Modbus *myModbus=new My_Modbus() ;
    mainBackend.setMyModbus(myModbus);
}
//调用dowInit的初始数据，关联
TEST_F(TestBackend,3)
{
    DowInit *dowInit=new DowInit ();
    mainBackend.setDowInit(dowInit);
}


#endif // TST_MAINBACKEND_H

