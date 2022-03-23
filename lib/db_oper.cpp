#include "db_oper.h"
#include <QSqlQuery>
#include <QDebug>
DB_oper::DB_oper(QObject *parent) : QObject(parent)
{

}

QVariantList DB_oper::getOperNames()
{
    QVariantList  operNames;
    QSqlQuery query;
    query.exec("select name from oper");
    while (query.next()) {
        operNames.append(query.value(0).toString());
    }
//    qDebug()<<operNames;
    return operNames;
}

int DB_oper::getOperIdbyName(QString operName)
{
    QSqlQuery query;
    query.prepare("select id_oper from oper where name=:operName");
    query.bindValue(":operName",operName);
    query.exec();
    query.next();
    qDebug()<<query.value(0);
    return query.value(0).toInt();
}


