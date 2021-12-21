
#ifndef TEST_ALARM_H
#define TEST_ALARM_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QModbusDataUnit>
#include <hwwalarm.h>
#pragma execution_character_set("utf-8")
//������Ϣ--����--״̬
TEST(Test_alarm,1){
    HwwAlarm hwwAlarm("2#�¶ȱ���",AlarmState::generate);
    ASSERT_EQ(hwwAlarm.content(),"2#�¶ȱ���");
    ASSERT_EQ(hwwAlarm.state(),AlarmState::generate);
    QString alarm1="1#�¶ȱ�����";
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
//������Ϣ��  ��Ա
TEST_F(Test_alarms,1)
{
    //������dowInit��ʼ����ֵ
    ASSERT_EQ(hwwAlarms->getInit_alarms().size(),8);
}

//����ask_plc_for_alarm,ͨ����PLC��ȡ������Ϣ���emit,��ȡ��Ϣ(�����ڲ�һ��ʱ��emit)
//�б仯��λ--�仯λ��ֵ
TEST_F(Test_alarms,tem1_over){
    int previous_alarms=0;
    int just_alarms=1;
    hwwAlarms->getAlarm_form_plc_signal(previous_alarms,just_alarms);
    QList<QString> alarmInfos=hwwAlarms->getAlarmsInfo();
    ASSERT_EQ(alarmInfos.count(),1);
    QString alarm="1#�¶ȹ��߱�������!";
    ASSERT_EQ(alarmInfos[0],alarm);

}

TEST_F(Test_alarms,tem1_normal){
    int previous_alarms=1;
    int just_alarms=0;
    hwwAlarms->getAlarm_form_plc_signal(previous_alarms,just_alarms);
    QList<QString> alarmInfos=hwwAlarms->getAlarmsInfo();
    ASSERT_EQ(alarmInfos.count(),1);
    ASSERT_EQ(alarmInfos[0],"1#�¶ȹ��߱����ѽ��!");
}
TEST_F(Test_alarms,tem12_over){  //ͨ������ȡ�仯����λ--��ȡ���λ��ֵ--���������
    int previous_alarms=0;
    int just_alarms=3;
    hwwAlarms->getAlarm_form_plc_signal(previous_alarms,just_alarms);
    QList<QString> alarmInfos=hwwAlarms->getAlarmsInfo();
    ASSERT_EQ(alarmInfos.count(),2);
    ASSERT_EQ(alarmInfos[0],"1#�¶ȹ��߱�������!");
    ASSERT_EQ(alarmInfos[1],"2#�¶ȹ��߱�������!");
}




#endif
