#include "dowinit.h"
#include "syspara.h"

#include <QtSql/QSqlDatabase>
#pragma execution_character_set("utf-8")
void DowInit::addSensor()
{
    //1.气体流量 2.气体压力 3.液体流量  4.转速  5~9.温度1  温度2。。。温度5
    Sensor *airFlow=new Sensor ("气体流量",0,0);
    Sensor *ariPress=new Sensor ("气体压力",0,2);
    Sensor *liquidFlow=new Sensor ("液体流量",0,4);
    Sensor *rotateSpeed=new Sensor ("搅拌转速",0,6);

    Sensor *tem1=new Sensor("1#温度",1,0);
    Sensor *tem2=new Sensor ("2#温度",1,1);
    Sensor *tem3=new Sensor ("3#温度",1,2);
    Sensor *tem4=new Sensor ("4#温度",1,3);
    Sensor *tem5=new Sensor ("5#温度",1,4);
    signalVals.append(airFlow);
    signalVals.append(ariPress);
    signalVals.append(liquidFlow);
    signalVals.append(rotateSpeed);

    tempSignalVals.append(tem1);
    tempSignalVals.append(tem2);
    tempSignalVals.append(tem3);
    tempSignalVals.append(tem4);
    tempSignalVals.append(tem5);
}



int DowInit::getRealTimeCurve_x_count() const
{
    return realTimeCurve_time_s/flashRealTimeCurve_s;

}






int DowInit::getRealTimeCurve_time_s() const
{
    SysPara syspara;
    return syspara.getRealTimeCurve_time_s_from_db();

}

void DowInit::setRealTimeCurve_time_s(int value)
{
    SysPara syspara;
    syspara.setRealTimeCurve_time_s_to_db(value);

    realTimeCurve_time_s = value;
}

int DowInit::getFlashRealTimeCurve_s() const
{
    SysPara syspara;
    return syspara.getRealTimeCureve_flashcycle_s_from_db();
}

void DowInit::setFlashRealTimeCurve_s(int value)
{
    SysPara syspara;
    syspara.setRealTimeCureve_flashcycle_s_to_db(value);
    flashRealTimeCurve_s = value;
}

QList<Para_with_plc> DowInit::getPara_with_plc()
{
    return paras;
}





int DowInit::getAskPlc_cycle_ms() const
{
    SysPara syspara;
    return syspara.getAskPlc_cycle_ms_from_db();

}

void DowInit::setAskPlc_cycle_ms(int value)
{
    SysPara syspara;
    syspara.setAskPlc_cycle_ms_to_db(value);
    askPlc_cycle_ms = value;
}

int DowInit::getRecord_cycle_s() const
{
    SysPara syspara;
    return syspara.getRecordRecycle_s_from_db();
}

void DowInit::setRecord_cycle_s(int value)
{
    SysPara syspara;
    syspara.setRecordCycle_s_to_db(value);
    record_cycle_s = value;
}

OutPutStates DowInit::getOutPutStates()
{
    return m_outPutStates;
}





void DowInit::addPara_with_plc()
{
    Para_with_plc temp1_alarm_high("1#温度高位报警",TreatmentMethod::x10,110);
    Para_with_plc temp2_alarm_high("2#温度高位报警",TreatmentMethod::x10,110);
    Para_with_plc temp1_increase_alarm("1#温度快速升温",TreatmentMethod::none,5);

    Para_with_plc air_flow_alarm_low("气体流量",TreatmentMethod::to_float,5);
    Para_with_plc liquid_flow_alarm_low("液体流量",TreatmentMethod::to_float,5);
    Para_with_plc rotate_speed_alarm_low("转速",TreatmentMethod::to_float,10);
    Para_with_plc air_press_alarm_high("气体压力",TreatmentMethod::to_float,10);
    Para_with_plc temp_fallback("温度回差",TreatmentMethod::x10,5);
    paras<<temp1_alarm_high<<temp2_alarm_high<<temp1_increase_alarm<<air_flow_alarm_low<<liquid_flow_alarm_low<<rotate_speed_alarm_low<<air_press_alarm_high<<temp_fallback;
}

void DowInit::getPara()
{
    //读取周期单位（ms)
    askPlc_cycle_ms=getAskPlc_cycle_ms();
    //记录周期s
    record_cycle_s=getRecord_cycle_s();
    //实时曲线显示时长（s)
    realTimeCurve_time_s=getRealTimeCurve_time_s();  //FIXME:好像横坐标是个数，而不是时间
    //实时曲线刷新时间(s)
    flashRealTimeCurve_s=getFlashRealTimeCurve_s();
}

//HwwAlarms* DowInit::getInitAlarms() const
//{
//    return m_initAlarms;
//}





void DowInit::add_out_put_state()
{
    OutPutState outPutState("加热器工作",false);
    OutPutState outPutState1("搅拌器工作",false);
    OutPutState outPutState2("1#蠕动泵工作",false);
    OutPutState outPutState3("2#蠕动泵工作",false);
    OutPutState outPutState4("电磁阀",false);
    m_outPutStates.add(outPutState);
    m_outPutStates.add(outPutState1);
    m_outPutStates.add(outPutState2);
    m_outPutStates.add(outPutState3);
    m_outPutStates.add(outPutState4);
}

DowInit::DowInit(QObject *parent) : QObject(parent)
{

    addSensor();

    getPara();

    addPara_with_plc();
    //添加输出点状态组
    add_out_put_state();



    if(!db.isOpen())
    {


        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("localhost");      //设置数据库主机名
        db.setDatabaseName("dow_experiment_data.db");  //设置数据库名称
        db.setUserName("cjkj");         //设置用户名
        db.setPassword("cjkj5215");     //设置密码
        db.open();
    }



}

int DowInit::getSignalValsNum()
{


    return signalVals.size();
}

int DowInit::getTempSignalValsNum()
{
    return tempSignalVals.size();
}




