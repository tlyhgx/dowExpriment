#include "backend_adjust_analog_set.h"
#include <QDebug>
#include <DB_Adjust_Analog>

Backend_adjust_analog_set::Backend_adjust_analog_set(QObject *parent) : QObject(parent)
{

}

void Backend_adjust_analog_set::setTem_vals(QVariantList tem_vals)
{
    //判断输入值是否为零，否则先从数据库读取对应值，然后经过计算写入数据库
    float valItem;
    for(int i=0;i<tem_vals.size();i++)
    {

        valItem=tem_vals[i].toFloat();

        if (valItem!=0)
        {
            qDebug()<<valItem;
        }
    }
}





