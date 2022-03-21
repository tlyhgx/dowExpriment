#ifndef BACKEND_ADJUST_ANALOG_SET_H
#define BACKEND_ADJUST_ANALOG_SET_H

#include <QObject>
#include<QVariantList>
#pragma execution_character_set("utf-8")
#include "db_adjust_analog.h"

class Backend_adjust_analog_set : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList tem_vals  WRITE setTem_vals )

    //FIXME:¿¼ÂÇnotice
public:
    explicit Backend_adjust_analog_set(QObject *parent = nullptr);


    void setTem_vals(QVariantList tem_vals);

signals:

private:
    DB_Adjust_Analog db_adjust_analog;
};

#endif // BACKEND_ADJUST_ANALOG_SET_H
