#ifndef DB_SIGNAL_VALS_H
#define DB_SIGNAL_VALS_H

#include <QObject>

class DB_signal_vals : public QObject
{
    Q_OBJECT
public:
    explicit DB_signal_vals(QObject *parent = nullptr);
    //ͨ��id_experiment��ģ�������ƻ�ȡ���飨ʱ�䡢����  ��ͬһ��list�У�
    QVariantList getTimeAndAnalogValByIDAndAnalogName(int id_experiment,QString analogName);
signals:

};

#endif // DB_SIGNAL_VALS_H
