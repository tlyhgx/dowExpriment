#include "db_signal_vals.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QDateTime>
DB_signal_vals::DB_signal_vals(QObject *parent) : QObject(parent)
{

}

QVariantList DB_signal_vals::getTimeAndAnalogValByIDAndAnalogName(int id_experiment,QString analogName)
{
    //获取时间和数据组合数组
    QVariantList com_time_val;
    QSqlQuery query;
    QString sqlString;
    qint64 ms;

    sqlString=QString("select create_time,value from signal_vals where  id_experiment = %1 and name='%2'").arg(id_experiment).arg(analogName);

    query.exec(sqlString);



    while (query.next()) {
        ms=(QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd hh:mm:ss")).toMSecsSinceEpoch();
        com_time_val.append(ms);
        com_time_val.append(query.value(1));
    }


    qDebug()<<com_time_val;


    return com_time_val;
}
