#ifndef REALTIMECURVEBACKEND_H
#define REALTIMECURVEBACKEND_H

#include <QObject>
//#include "mymodbus.h"
#include "dowinit.h"
#include "getplcval.h"
#include <QTimer>
class RealTimeCurveBackend : public QObject
{
    Q_OBJECT
    ///x轴的个数（时间坐标）
    Q_PROPERTY(int x_count READ x_count  )
public:
    explicit RealTimeCurveBackend(DowInit *dowInit,GetPlcVal *getPlcVal,QObject *parent = nullptr);

public:
    int x_count();

public slots:

    void emit_val_to_view();
signals:
    ///通知界面，有数据变化
    /// \brief signalValChanged
    /// \param signalVals
    ///
    void signalValChanged(QVariantList signalVals);
private:
    DowInit* dowInit;
    GetPlcVal *getPlcVal;
    QTimer *timer_realTimeCurve;
    QVariantList signalVals;
    QVariantList otherSignalVals;
    QVariantList tempSignalVals;

};

#endif // REALTIMECURVEBACKEND_H
