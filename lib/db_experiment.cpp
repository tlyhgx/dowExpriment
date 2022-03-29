#include "db_experiment.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
DB_experiment::DB_experiment(QObject *parent) : QObject(parent)
{

}

QVariantList DB_experiment::getNameByOperID(int id_oper)
{
    QVariantList experiment_names;
    QSqlQuery query;

    query.prepare("select name from experiment where id_oper=:id_oper ORDER BY create_time DESC");
    query.bindValue(":id_oper",id_oper);
    query.exec();
    while (query.next()) {
        experiment_names.append(query.value(0));
    }

//    qDebug()<<experiment_names;
    return experiment_names;
}

int DB_experiment::getExperimentIdByName(QString experimentName)
{
    int id_experiment;
    QSqlQuery query;

    query.prepare("select id_experiment from experiment where name=:name ORDER BY create_time DESC");
    query.bindValue(":name",experimentName);
    query.exec();
    query.next();
    id_experiment=query.value(0).toInt();

    return id_experiment;
}
