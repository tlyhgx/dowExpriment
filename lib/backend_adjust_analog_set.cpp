#include "backend_adjust_analog_set.h"
#include <QDebug>


Backend_adjust_analog_set::Backend_adjust_analog_set(QObject *parent) : QObject(parent)
{

}

void Backend_adjust_analog_set::setTem_vals(QVariantList tem_vals)
{
    //判断输入值是否为零，否则先从数据库读取对应值，然后经过计算写入数据库

    QVector<float> adjusted_vals;
    QVector<float> db_adjust_vals= db_adjust_analog.getAdjustVals();
    for(int i=0;i<db_adjust_vals.size();i++)
    {

        adjusted_vals.append(db_adjust_vals[i]+tem_vals[i].toFloat());
    }

    db_adjust_analog.setAdjustVals(adjusted_vals);
}





