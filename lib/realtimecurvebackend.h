﻿#ifndef REALTIMECURVEBACKEND_H
#define REALTIMECURVEBACKEND_H

#include <QObject>
#include "mymodbus.h"
#include "dowinit.h"
class RealTimeCurveBackend : public QObject
{
    Q_OBJECT
public:
    explicit RealTimeCurveBackend(DowInit *dowInit,MyModbus *mymodbus,QObject *parent = nullptr);


public slots:
    ///当PLC有数据发送时，获取数据，并做处理
    /// \brief getSignalVals
    /// \param dataUnit
    /// \return
    /// 提供给界面的值
    QVariantList getSignalVals(QModbusDataUnit dataUnit);
signals:
    ///通知界面，有数据变化
    /// \brief signalValChanged
    /// \param signalVals
    ///
    void signalValChanged(QVariantList signalVals);
private:
    DowInit* dowInit;
    MyModbus *myModbus;
    QVariantList signalVals;
};

#endif // REALTIMECURVEBACKEND_H
