#include "backend_adjust_analog_set.h"
#include <QDebug>
#include <DB_Adjust_Analog>

Backend_adjust_analog_set::Backend_adjust_analog_set(QObject *parent) : QObject(parent)
{

}

void Backend_adjust_analog_set::setTem_vals(QVariantList tem_vals)
{
    //�ж�����ֵ�Ƿ�Ϊ�㣬�����ȴ����ݿ��ȡ��Ӧֵ��Ȼ�󾭹�����д�����ݿ�
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





