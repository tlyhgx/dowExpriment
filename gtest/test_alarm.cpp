
#ifndef TEST_ALARM_H
#define TEST_ALARM_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QModbusDataUnit>
#include <hwwalarm.h>
#pragma execution_character_set("utf-8")
//报警信息--内容--状态
TEST(Test_alarm,1){
    HwwAlarm hwwAlarm("2#温度报警",AlarmState::generate);
    ASSERT_EQ(hwwAlarm.content(),"2#温度报警");
    ASSERT_EQ(hwwAlarm.state(),AlarmState::generate);
    QString alarm1="1#温度报警！";
    hwwAlarm.setContent(alarm1);
    ASSERT_EQ(alarm1,hwwAlarm.content());

    hwwAlarm.setState(AlarmState::generate);
    ASSERT_EQ(hwwAlarm.state(),AlarmState::generate);

    hwwAlarm.setState(AlarmState::handled);
    ASSERT_EQ(hwwAlarm.state(),AlarmState::handled);
    hwwAlarm.setState(AlarmState::none);
    ASSERT_EQ(hwwAlarm.state(),AlarmState::none);
}

class Test_alarms:public testing::Test{
 public:
    DowInit dowInit;
    MyModbus myModbus;
    GetPlcVal *getPlcVal;
    HwwAlarms *hwwAlarms;
    // Test interface
protected:
    void SetUp() override;
};

void Test_alarms::SetUp()
{
    getPlcVal=new GetPlcVal(&dowInit,&myModbus);
    hwwAlarms=new HwwAlarms (getPlcVal);
}
//报警信息组  成员
TEST_F(Test_alarms,1)
{
    //报警在dowInit初始化赋值
    ASSERT_EQ(hwwAlarms->getInit_alarms().size(),8);
}

//发送ask_plc_for_alarm,通过从PLC获取报警信息后的emit,获取信息(报警在不一样时才emit)
//有变化的位--变化位的值
TEST_F(Test_alarms,tem1_over){
    int previous_alarms=0;
    int just_alarms=1;
    hwwAlarms->getAlarm_form_plc_signal(previous_alarms,just_alarms);
    QList<QString> alarmInfos=hwwAlarms->getAlarmsInfo();
    ASSERT_EQ(alarmInfos.count(),1);
    QString alarm="1#温度过高报警生成!";
    ASSERT_EQ(alarmInfos[0],alarm);

}

TEST_F(Test_alarms,tem1_normal){
    int previous_alarms=1;
    int just_alarms=0;
    hwwAlarms->getAlarm_form_plc_signal(previous_alarms,just_alarms);
    QList<QString> alarmInfos=hwwAlarms->getAlarmsInfo();
    ASSERT_EQ(alarmInfos.count(),1);
    ASSERT_EQ(alarmInfos[0],"1#温度过高报警已解除!");
}
TEST_F(Test_alarms,tem12_over){  //通过异或获取变化所在位--读取相关位的值--输出报警组
    int previous_alarms=0;
    int just_alarms=3;
    hwwAlarms->getAlarm_form_plc_signal(previous_alarms,just_alarms);
    QList<QString> alarmInfos=hwwAlarms->getAlarmsInfo();
    ASSERT_EQ(alarmInfos.count(),2);
    ASSERT_EQ(alarmInfos[0],"1#温度过高报警生成!");
    ASSERT_EQ(alarmInfos[1],"2#温度过高报警生成!");
}




#endif
