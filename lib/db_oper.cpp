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
    query.exec("select name from oper order by id_oper");
    while (query.next()) {
        operNames.append(query.value(0).toString());
    }
//    qDebug()<<operNames;
    return operNames;
}

int DB_oper::getOperIdbyName(QString operName)
{
    QSqlQuery query;
    query.prepare("select id_oper from oper where name=:operName ");
    query.bindValue(":operName",operName);
    query.exec();
    query.next();
    qDebug()<<query.value(0);
    return query.value(0).toInt();
}

void DB_oper::addOperName(QString operName)
{

    QSqlQuery query;
    query.prepare("insert into oper (name) values (:operName)");
    query.bindValue(":operName",operName);
    query.exec();

}

void DB_oper::delOperName(QString operName)
{
    //需要级联删除

    //通过用户名查找用户名_id
    QSqlQuery query;
    QString sql=QString("select id_oper from oper where name='%1'").arg(operName);
    query.exec(sql);
    query.next();
    int id_oper=query.value(0).toInt();

    //通过用户名_id查找实验名称_id组
    query.clear();
    sql=QString("select id_experiment from experiment where id_oper=%1").arg(id_oper);
    query.exec(sql);

    //--》通过实验名称_id删除实验数据；
    QSqlQuery query_del_signal_vals;
    while (query.next()) {
        sql=QString("delete from signal_vals   where id_experiment=%1").arg(query.value(0).toInt());
        query_del_signal_vals.exec(sql);
    }

    //删除实验名称
    query.clear();
    sql=QString("delete  from experiment where id_oper=%1").arg(id_oper);
    query.exec(sql);

    //删除用户名
    query.clear();
    sql=QString("delete  from oper where id_oper=%1").arg(id_oper);
    query.exec(sql);

}

void DB_oper::update_oper(QString operName,QString last_name)
{
    QSqlQuery query;
    QString sql=QString("update oper set name='%1' where name='%2'").arg(operName).arg(last_name);
    query.exec(sql);
}


