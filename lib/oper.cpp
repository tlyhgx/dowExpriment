#include "oper.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <dowdatabase.h>
#pragma execution_character_set("utf-8")
Oper::Oper(QObject *parent) : QObject(parent)
{

    DowDataBase::openDB();

}

bool Oper::addOneOper_to_db(QString name, QString password, QString permission)
{
    DowDataBase::openDB();
    QSqlQuery query;

    bool res=query.exec(QString("insert into oper(name, password,permission)"
                          "VALUES ('%1', '%2','%3')").arg(name).arg(password).arg(permission));
    return res;
}

int Oper::findLastOper_id_by_name_from_db(QString name)
{
    QSqlQuery q(QString("select id_oper from oper where name='%1' ").arg(name));
    QSqlRecord rec=q.record();

    if(q.next()){
       return q.value(0).toInt();
    }
    else{
        return -1;
    }

}

QString Oper::find_name_by_id_from_db(int id)
{
    QSqlQuery q(QString("select name from oper where id_oper='%1'").arg(id));
    QSqlRecord rec=q.record();
    int nameCol=rec.indexOf("name");
    q.next();

    return q.value(nameCol).toString();
}


