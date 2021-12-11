#ifndef EXPRIMENT_H
#define EXPRIMENT_H

#include <QObject>

class Experiment : public QObject
{
    Q_OBJECT
public:
    explicit Experiment(QObject *parent = nullptr);
    void addExpriment_to_db(QString csExprimentName="สตั้ร๛ณฦ1",int id_oper=1);
    int findLastExpriment_id_by_name_from_db(QString exprimentName);
signals:

};

#endif // EXPRIMENT_H
