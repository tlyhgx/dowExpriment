#include "backend_oper_manage.h"

void Backend_oper_manage::add_oper(QString operName)
{
    if(operName!="")
    db_oper.addOperName(operName);
}

Backend_oper_manage::Backend_oper_manage(QObject *parent) : QObject(parent)
{

}

QVariantList Backend_oper_manage::list_operName()
{

    //从数据库读取所有实验人员名称



    return db_oper.getOperNames();

}
