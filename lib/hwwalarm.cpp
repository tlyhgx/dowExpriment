#include "hwwalarm.h"
#include "hwwutility.h"


#pragma execution_character_set("utf-8")
HwwAlarm::HwwAlarm(QString content, AlarmState state, QObject *parent):
    m_content(content),m_state(state)
{

}

QString HwwAlarm::content() const
{
    return m_content;
}

void HwwAlarm::setContent(const QString &content)
{
    m_content = content;
}

AlarmState HwwAlarm::state() const
{
    return m_state;
}

void HwwAlarm::setState(const AlarmState &state)
{
    m_state = state;
}



void HwwAlarms::getAlarm_form_plc_signal(int prevous_alarms, int just_alarms)
{
    m_alarmsInfo.clear();
    //��ȡ״̬�ı���
    vector<int> xors_positions= HwwUtility::xor_get_diff(prevous_alarms,just_alarms);
    //��״̬�ı��Ӧλ�ã���ȡ��Ϣ
    //��Ϣ��״̬
    vector<int> just_alarm_val=HwwUtility::int_vector_int_0_1(just_alarms);
    for(int i=0;i<m_init_alarms.size();i++){
        if(xors_positions[i]==1){
            QString alarmInfo;
            if(just_alarm_val[i]==0){
                m_alarmsInfo<<m_init_alarms[i]->content()+"�ѽ��!";
                alarmInfo=m_init_alarms[i]->content()+"�ѽ��!";
            }else if(just_alarm_val[i]==1)
            {
                m_alarmsInfo<<m_init_alarms[i]->content()+"����!";
                alarmInfo=m_init_alarms[i]->content()+"����!";
            }

            emit makeAlarmInfo(alarmInfo);
        }

    }


}

HwwAlarms::HwwAlarms(GetPlcVal *getPlcVal)
{
    this->getPlcVal=getPlcVal;
    connect(getPlcVal,&GetPlcVal::alarmsChanged,this,&HwwAlarms::getAlarm_form_plc_signal);
    HwwAlarm *hwwalarm1=new HwwAlarm("1#�¶ȹ��߱���",AlarmState::none);
    HwwAlarm *hwwalarm2=new HwwAlarm("2#�¶ȹ��߱���",AlarmState::none);
    HwwAlarm *hwwalarm3=new HwwAlarm("1#�¶��������챨��",AlarmState::none);
    HwwAlarm *hwwalarm4=new HwwAlarm("����������������",AlarmState::none);
    HwwAlarm *hwwalarm5=new HwwAlarm("Һ��������������",AlarmState::none);
    HwwAlarm *hwwalarm6=new HwwAlarm("�����������",AlarmState::none);
    HwwAlarm *hwwalarm7=new HwwAlarm("����ѹ�����󱨾�",AlarmState::none);
    HwwAlarm *hwwalarm8=new HwwAlarm("ϵͳ����",AlarmState::none);
    m_init_alarms.append(hwwalarm1);
    m_init_alarms.append(hwwalarm2);
    m_init_alarms.append(hwwalarm3);
    m_init_alarms.append(hwwalarm4);
    m_init_alarms.append(hwwalarm5);
    m_init_alarms.append(hwwalarm6);
    m_init_alarms.append(hwwalarm7);
    m_init_alarms.append(hwwalarm8);
}



void HwwAlarms::append(HwwAlarm *hwwAlarm)
{
    m_init_alarms<<hwwAlarm;
}

QList<QString> HwwAlarms::getAlarmsInfo() const
{
    return m_alarmsInfo;
}

QList<HwwAlarm*> HwwAlarms::getInit_alarms() const
{
    return m_init_alarms;
}






