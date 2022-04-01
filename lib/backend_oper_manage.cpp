#include "backend_oper_manage.h"

void Backend_oper_manage::add_oper(QString operName)
{
    if(operName!="")
    {
        db_oper.addOperName(operName);
        //重新搜索，并刷新
        refresh_list_oper_name();
    }
}

void Backend_oper_manage::del_oper(QString operName)
{
    if(operName!="")
    {
        db_oper.delOperName(operName);
        //重新搜索，并刷新
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

        //重新搜索，并刷新
        refresh_list_oper_name();
        }
}

Backend_oper_manage::Backend_oper_manage(QObject *parent) : QObject(parent)
{
//    connect(this,Backend_oper_manage::list_operNameChanged,)
}

QVariantList Backend_oper_manage::list_operName()
{

    //从数据库读取所有实验人员名称



    return db_oper.getOperNames();

}
