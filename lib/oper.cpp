#include "oper.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

Oper::Oper(QObject *parent) : QObject(parent)
{
    if(!db.isOpen())
    {


        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("localhost");      //设置数据库主机名
        db.setDatabaseName("dow_experiment_data.db");  //设置数据库名称
        db.setUserName("cjkj");         //设置用户名
        db.setPassword("cjkj5215");     //设置密码
        db.open();
    }
}

bool Oper::addOneOper_to_db(QString name, QString password, QString permission)
{
    QSqlQuery query;


    bool res=query.exec(QString("insert into oper(name, password,permission)"
                          "VALUES ('%1', '%2','%3')").arg(name).arg(password).arg(permission));
    return res;
}

int Oper::findLastOper_id_by_name_from_db(QString name)
{
    QSqlQuery q(QString("select id_oper from oper where name='%1' ").arg(name));
    QSqlRecord rec=q.record();
    int idCol=rec.indexOf("id_oper");
    q.next();
    return q.value(idCol).toInt();
}

QString Oper::find_name_by_id_from_db(int id)
{
    QSqlQuery q(QString("select name from oper where id_oper='%1'").arg(id));
    QSqlRecord rec=q.record();
    int nameCol=rec.indexOf("name");
    q.next();

    return q.value(nameCol).toString();
}


