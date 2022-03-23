#ifndef DB_SIGNAL_VALS_H
#define DB_SIGNAL_VALS_H

#include <QObject>

class DB_signal_vals : public QObject
{
    Q_OBJECT
public:
    explicit DB_signal_vals(QObject *parent = nullptr);
    //通过id_experiment和模拟量名称获取数组（时间、数据  在同一个list中）
    QVariantList getTimeAndAnalogValByIDAndAnalogName(int id_experiment,QString analogName);
signals:

};

#endif // DB_SIGNAL_VALS_H
