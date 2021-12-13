#include "dowdatabase.h"
#include "syspara.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
SysPara::SysPara(QObject *parent) : QObject(parent)
{
    DowDataBase::openDB();

    QSqlQuery query;
    query.exec("select * from sys_para");
    if(!query.next()){
        query.exec("insert into sys_para(record_cycle_s) VALUES('5')");
    }

}

int SysPara::getRecordRecycle_s_from_db()
{
    QSqlQuery query;
    query.exec("select record_cycle_s from sys_para");
    query.next();
    return query.value(0).toInt();
}

void SysPara::setRecordCycle_s_to_db(int recordCycle_s)
{
    QSqlQuery query;
    query.exec(QString("update sys_para set record_cycle_s ='%1' ").arg(recordCycle_s));
}
