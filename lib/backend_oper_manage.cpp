#include "backend_oper_manage.h"
#include "db_oper.h"
Backend_oper_manage::Backend_oper_manage(QObject *parent) : QObject(parent)
{

}

QVariantList Backend_oper_manage::list_operName()
{

    //�����ݿ��ȡ����ʵ����Ա����
    DB_oper db_oper;


    return db_oper.getOperNames();

}
