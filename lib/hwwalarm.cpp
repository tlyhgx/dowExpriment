#include "hwwalarm.h"
#include "hwwutility.h"
#include <qtextcodec.h>

HwwAlarm::HwwAlarm(QString content, AlarmState state, QObject *parent):
    m_content(content),m_state(state)
{
    Q_UNUSED(parent);
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
    //获取状态改变组
    vector<int> xors_positions= HwwUtility::xor_get_diff(prevous_alarms,just_alarms);
    //从状态改变对应位置，获取信息
    //信息加状态
    vector<int> just_alarm_val=HwwUtility::int_vector_int_0_1(just_alarms);
    for(int i=0;i<m_init_alarms.size();i++){
        if(xors_positions[i]==1){

            QString alarmInfo;
            if(just_alarm_val[i]==0){
                m_alarmsInfo<<m_init_alarms[i]->content()+codec->toUnicode("已解除!");

                alarmInfo=m_init_alarms[i]->content()+codec->toUnicode("已解除!");


            }else if(just_alarm_val[i]==1)
            {
                m_alarmsInfo<<m_init_alarms[i]->content()+codec->toUnicode("生成!");
                alarmInfo=m_init_alarms[i]->content()+codec->toUnicode("生成!");
            }
//            emit makeAlarmInfo("测试");
//            emit makeAlarmInfo(QObject::tr(alarmInfo.toLatin1().data()) );
//            emit makeAlarmInfo(u8"测试");


            emit makeAlarmInfo(alarmInfo);
        }

    }


}

HwwAlarms::HwwAlarms(GetPlcVal *getPlcVal)
{
    this->getPlcVal=getPlcVal;
    connect(getPlcVal,&GetPlcVal::alarmsChanged,this,&HwwAlarms::getAlarm_form_plc_signal);
    codec = QTextCodec::codecForName("GBK");
    HwwAlarm *hwwalarm1=new HwwAlarm(codec->toUnicode("1#温度过高报警"),AlarmState::none);
    HwwAlarm *hwwalarm2=new HwwAlarm(codec->toUnicode("2#温度过高报警"),AlarmState::none);
    HwwAlarm *hwwalarm3=new HwwAlarm(codec->toUnicode("1#温度上升过快报警"),AlarmState::none);
    HwwAlarm *hwwalarm4=new HwwAlarm(codec->toUnicode("气体流动过慢报警"),AlarmState::none);
    HwwAlarm *hwwalarm5=new HwwAlarm(codec->toUnicode("液体流动过慢报警"),AlarmState::none);
    HwwAlarm *hwwalarm6=new HwwAlarm(codec->toUnicode("搅拌过慢报警"),AlarmState::none);
    HwwAlarm *hwwalarm7=new HwwAlarm(codec->toUnicode("气体压力过大报警"),AlarmState::none);
    HwwAlarm *hwwalarm8=new HwwAlarm(codec->toUnicode("系统运行"),AlarmState::none);
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






