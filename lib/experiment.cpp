#include "experiment.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

Experiment::Experiment(QObject *parent) : QObject(parent)
{

}

void Experiment::addExpriment_to_db(QString csExprimentName, int id_oper)
{
    QSqlQuery query;
    query.exec(QString("insert into experiment(name, id_oper)"
                              "VALUES ('%1', '%2')").arg(csExprimentName).arg(id_oper));
}

int Experiment::findLastExpriment_id_by_name_from_db(QString exprimentName)
{
    QSqlQuery q(QString("select id_experiment from experiment where name=='%1' ").arg(exprimentName));
    QSqlRecord rec=q.record();
    int idCol=rec.indexOf("id_experiment");
    if(q.next()){
       return q.value(idCol).toInt();
    }
    else{
        return -1;
    }
}
