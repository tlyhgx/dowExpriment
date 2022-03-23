#ifndef DB_EXPERIMENT_H
#define DB_EXPERIMENT_H

#include <QObject>

class DB_experiment : public QObject
{
    Q_OBJECT
public:
    explicit DB_experiment(QObject *parent = nullptr);
    QVariantList getNameByOperID(int id_oper);
    int getExperimentIdByName(QString experimentName);
signals:

};

#endif // DB_EXPERIMENT_H
