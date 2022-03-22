#ifndef DB_ADJUST_ANALOG_H
#define DB_ADJUST_ANALOG_H

#include <QObject>

class DB_Adjust_Analog : public QObject
{
    Q_OBJECT
public:
    explicit DB_Adjust_Analog(QObject *parent = nullptr);
    QVector<float> getAdjustVals();
    void setAdjustVals(QVector<float> ajusted_vals);
signals:

};

#endif // DB_ADJUST_ANALOG_H
