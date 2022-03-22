#include "db_adjust_analog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
DB_Adjust_Analog::DB_Adjust_Analog(QObject *parent) : QObject(parent)
{

}

QVector<float> DB_Adjust_Analog::getAdjustVals()
{
    QVector<float> adjust_vals;
    QSqlQuery query;
    query.exec("select * from adjust_analog_val");
    query.next();
    QSqlRecord rec=query.record();
    for(int i=0;i<rec.count();i++)
    {

        adjust_vals.append(query.value(i).toFloat());
    }
//    qDebug()<<adjust_vals.count();
    return adjust_vals;

}

void DB_Adjust_Analog::setAdjustVals(QVector<float> adjusted_vals)
{
    QSqlQuery query;
    query.prepare("UPDATE adjust_analog_val set adjust_val1=:val1, adjust_val2=:val2, adjust_val3=:val3, adjust_val4=:val4 ,adjust_val5=:val5 where rowid=1");
    query.bindValue(":val1",adjusted_vals[0]);
    query.bindValue(":val2",adjusted_vals[1]);
    query.bindValue(":val3",adjusted_vals[2]);
    query.bindValue(":val4",adjusted_vals[3]);
    query.bindValue(":val5",adjusted_vals[4]);
query.exec();


}
