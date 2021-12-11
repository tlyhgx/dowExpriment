#include "signal_vals.h"

#include <QSqlQuery>

Signal_vals::Signal_vals(QObject *parent) : QObject(parent)
{

}

void Signal_vals::add_val_to_db(float val)
{
    QSqlQuery query;
//    query.exec(QString("insert into oper(name, password,permission)"
//                              "VALUES ('%1', '%2','%3')").arg(name).arg(password).arg(permission));
}

float Signal_vals::get_val_from_db(int id_signal_val)
{
    return 15.3;
}
