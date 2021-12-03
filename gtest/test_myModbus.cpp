#ifndef TEST_MYMODBUS_H
#define TEST_MYMODBUS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "mymodbus.h"
#include "dowinit.h"
using namespace testing;

class TestMyModbus:public ::testing::Test{
public:
    DowInit dowInit;

    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;
};

void TestMyModbus::SetUp()
{

}

void TestMyModbus::TearDown()
{
}


//从dowInit导入modbus的基本参数 串口号
TEST_F(TestMyModbus, cs1)
{
    dowInit.modbusSetting.portName="COM2";
    MyModbus myModbus(dowInit);
    ASSERT_EQ(myModbus.m_settings.portName,"COM2");
}

//从dowInit导入modbus的基本参数 波特率
TEST_F(TestMyModbus, cs2)
{

    dowInit.modbusSetting.baud=QSerialPort::Baud115200;
    MyModbus myModbus(dowInit);
    ASSERT_EQ(myModbus.m_settings.baud,QSerialPort::Baud115200);
}

TEST_F(TestMyModbus, cs3)
{

    dowInit.modbusSetting.parity=QSerialPort::NoParity;
    MyModbus myModbus(dowInit);
    ASSERT_EQ(myModbus.m_settings.parity,QSerialPort::NoParity);
}

TEST_F(TestMyModbus, cs4)
{

    dowInit.modbusSetting.dataBits=QSerialPort::Data8;
    MyModbus myModbus(dowInit);
    ASSERT_EQ(myModbus.m_settings.dataBits,QSerialPort::Data8);
}

TEST_F(TestMyModbus, cs5)
{

    dowInit.modbusSetting.stopBits=QSerialPort::OneStop;
    MyModbus myModbus(dowInit);
    ASSERT_EQ(myModbus.m_settings.stopBits,QSerialPort::OneStop);
}

TEST_F(TestMyModbus, cs6)
{

    dowInit.modbusSetting.responseTime=1200;
    MyModbus myModbus(dowInit);
    ASSERT_EQ(myModbus.m_settings.responseTime,1200);
}

TEST_F(TestMyModbus, cs7)
{

    dowInit.modbusSetting.numberOfRetries=1;
    MyModbus myModbus(dowInit);
    ASSERT_EQ(myModbus.m_settings.numberOfRetries,1);
}


#endif // TEST_MYMODBUS_H

