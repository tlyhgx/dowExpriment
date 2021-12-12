#include "signal_vals.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

Signal_vals::Signal_vals(QObject *parent) : QObject(parent)
{

}

void Signal_vals::add_val_to_db(float val,QString name,int id_experiment)
{
    QSqlQuery query;
    query.exec(QString("insert into signal_vals(value, name,id_experiment)"
                              "VALUES ('%1', '%2','%3')").arg(val).arg(name).arg(id_experiment));
}

vector<float> Signal_vals::get_val_by_experimentId_from_db(int id_experiment)
{
    vector<float> ret;
    QSqlQuery q(QString("select value from signal_vals where    id_experiment='%1'").arg(id_experiment));
    q.record();
    while (q.next()) {
        ret.push_back(q.value(0).toFloat());
    }


    return ret;
}
