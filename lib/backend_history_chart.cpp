#include "backend_history_chart.h"
#include "db_oper.h"
#include <QDebug>
#include "db_experiment.h"
#include "db_signal_vals.h"
#include <QDateTime>
void Backend_history_chart::ask_datas_from_db()
{
    //通过实验名称找到实验_id
    int id_experiment;
    DB_experiment db_experiment;
    id_experiment=db_experiment.getExperimentIdByName(experimentName);
    //    qDebug()<<id_experiment;
    //通过实验_id和模拟量名字找到实验数据（含时间ms和数据）
    DB_signal_vals db_signal_vals;
    list_Com_Time_RecordVal=db_signal_vals.getTimeAndAnalogValByIDAndAnalogName(id_experiment,analogName);

    //显示值范围
    if(list_Com_Time_RecordVal.count()>=4)
    {
        float val_min,val_max,current_val,delta_val;

        current_val=list_Com_Time_RecordVal[1].toFloat();
        val_max=current_val;
        val_min=current_val;

        //搜索最大和最小值

        for(int i=1;i<list_Com_Time_RecordVal.count();i=i+2)
        {
            current_val=list_Com_Time_RecordVal[i].toFloat();
            if(current_val>val_max )
            {
                val_max=current_val;
            }
            if(current_val<val_min)
            {
                val_min=current_val;
            }
        }
        //调整范围
        delta_val=(val_max-val_min)*0.1;
        val_max=val_max+delta_val;
        val_min=val_min-delta_val;
        group_val_min_max.clear();

        group_val_min_max<<int(val_min);
        group_val_min_max<<int(val_max);
//        qDebug()<<group_val_min_max<<"最值";
        emit displayValueScopeChanged();
    }

    //首尾时间
    if(list_Com_Time_RecordVal.count()>=2)
    {
        group_time_start_end.clear();
        group_time_start_end<<QDateTime::fromMSecsSinceEpoch(list_Com_Time_RecordVal[0].toULongLong());
        group_time_start_end<<QDateTime::fromMSecsSinceEpoch(list_Com_Time_RecordVal[list_Com_Time_RecordVal.count()-2].toULongLong());
        //        qDebug()<<group_time_start_end;
        emit time_start_endChanged();
    }

    emit recieveTimeAndValChanged();
}

Backend_history_chart::Backend_history_chart(QObject *parent) : QObject(parent)
{
    connect(this,&Backend_history_chart::operNameChanged,this,&Backend_history_chart::experimentNames);
}



void Backend_history_chart::setAnalogName(const QString &analogName)
{
    this->analogName=analogName;
}



QVariantList Backend_history_chart::operNames()
{
    //通过数据库读取操作人员名字组
    DB_oper db_oper;

    QVariantList operNames=db_oper.getOperNames();

    return operNames;
}

void Backend_history_chart::setOperName(const QString &operName_input)
{
    operName=operName_input;
    //    qDebug()<<operName;
    emit operNameChanged();


}

void Backend_history_chart::setExperimentName(const QString &experimentName_input)
{
    experimentName=experimentName_input;
}

QVariantList Backend_history_chart::experimentNames()
{
    QVariantList list_experimentNames;
    //通过操作人员的姓名--》id_oper--》experiment_names
    int id_oper;
    DB_oper db_oper;
    id_oper=db_oper.getOperIdbyName(operName);
    DB_experiment db_experiment;
    list_experimentNames=db_experiment.getNameByOperID(id_oper);
    return list_experimentNames;
}

QVariantList Backend_history_chart::recieveTimeAndVal()
{
    return list_Com_Time_RecordVal;
}

QVariantList Backend_history_chart::displayValueScope()
{
    return group_val_min_max;
}

QVariantList Backend_history_chart::time_start_end()
{
    return group_time_start_end;
}
