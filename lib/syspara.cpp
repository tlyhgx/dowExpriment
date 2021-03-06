#include "dowdatabase.h"
#include "syspara.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#pragma execution_character_set("utf-8")
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

int SysPara::getRealTimeCureve_flashcycle_s_from_db()
{
    QSqlQuery query;
    query.exec("select realTimeCurve_flashcycle_s from sys_para");
    query.next();
    return query.value(0).toInt();
}

void SysPara::setRealTimeCureve_flashcycle_s_to_db(int realTimeCurve_flashcycle_s)
{
    QSqlQuery query;
    query.exec(QString("update sys_para set realTimeCurve_flashcycle_s ='%1' ").arg(realTimeCurve_flashcycle_s));
}

int SysPara::getRealTimeCurve_time_s_from_db()
{
    QSqlQuery query;
    query.exec("select realTimeCurve_time_s from sys_para");
    query.next();
    return query.value(0).toInt();
}

void SysPara::setRealTimeCurve_time_s_to_db(int realTimeCurve_time_s)
{
    QSqlQuery query;
    query.exec(QString("update sys_para set realTimeCurve_time_s ='%1' ").arg(realTimeCurve_time_s));
}

int SysPara::getAskPlc_cycle_ms_from_db()
{
    QSqlQuery query;
    query.exec("select askPlc_cycle_ms from sys_para");
    query.next();
    return query.value(0).toInt();
}

void SysPara::setAskPlc_cycle_ms_to_db(int askPlc_cycle_ms)
{
    QSqlQuery query;
    query.exec(QString("update sys_para set askPlc_cycle_ms ='%1' ").arg(askPlc_cycle_ms));
}


