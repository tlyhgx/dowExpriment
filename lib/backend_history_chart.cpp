#include "backend_history_chart.h"
#include "db_oper.h"
#include <QDebug>
Backend_history_chart::Backend_history_chart(QObject *parent) : QObject(parent)
{
    connect(this,&Backend_history_chart::operNameChanged,this,&Backend_history_chart::experimentNames);
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

QVariantList Backend_history_chart::experimentNames()
{
    QVariantList experimentNames;
    //通过操作人员的姓名--》id_oper--》experiment_names
    int id_oper;
    DB_oper db_oper;
    id_oper=db_oper.getOperIdbyName(operName);


    return experimentNames;
}
