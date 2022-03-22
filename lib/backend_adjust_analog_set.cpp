#include "backend_adjust_analog_set.h"
#include <QDebug>


Backend_adjust_analog_set::Backend_adjust_analog_set(QObject *parent) : QObject(parent)
{

}

void Backend_adjust_analog_set::setTem_vals(QVariantList tem_vals)
{
    //�ж�����ֵ�Ƿ�Ϊ�㣬�����ȴ����ݿ��ȡ��Ӧֵ��Ȼ�󾭹�����д�����ݿ�

    QVector<float> adjusted_vals;
    QVector<float> db_adjust_vals= db_adjust_analog.getAdjustVals();
    for(int i=0;i<db_adjust_vals.size();i++)
    {

        adjusted_vals.append(db_adjust_vals[i]+tem_vals[i].toFloat());
    }

    db_adjust_analog.setAdjustVals(adjusted_vals);
}





