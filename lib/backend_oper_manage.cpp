#include "backend_oper_manage.h"

void Backend_oper_manage::add_oper(QString operName)
{
    if(operName!="")
    {
        db_oper.addOperName(operName);
        //������������ˢ��
        refresh_list_oper_name();
    }
}

void Backend_oper_manage::del_oper(QString operName)
{
    if(operName!="")
    {
        db_oper.delOperName(operName);
        //������������ˢ��
        refresh_list_oper_name();
    }
}

void Backend_oper_manage::refresh_list_oper_name()
{
    this->list_operName();
    emit list_operNameChanged();
}

void Backend_oper_manage::update_oper(QString operName,QString last_name)
{
    if(operName!="")
        {db_oper.update_oper(operName,last_name);

        //������������ˢ��
        refresh_list_oper_name();
        }
}

Backend_oper_manage::Backend_oper_manage(QObject *parent) : QObject(parent)
{
//    connect(this,Backend_oper_manage::list_operNameChanged,)
}

QVariantList Backend_oper_manage::list_operName()
{

    //�����ݿ��ȡ����ʵ����Ա����



    return db_oper.getOperNames();

}
