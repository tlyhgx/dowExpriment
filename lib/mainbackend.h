#ifndef MAINBACKEND_H
#define MAINBACKEND_H

#include <QObject>
#include <QVariant>
#include "mymodbus.h"
#include "dowinit.h"
using namespace std;
class MainBackend : public QObject
{
    Q_OBJECT
public:
    explicit MainBackend(QObject *parent = nullptr);
    MainBackend(DowInit *dowInit,MyModbus *mymodbus,QObject *parent = nullptr);
public:
    Q_INVOKABLE void askSignalVals();
    Q_INVOKABLE QVariantList retSignalVals();
    void setMyModbus(MyModbus *myModbus);
    void setDowInit(DowInit *value);
public slots:
    QVariantList getSignalVals(QModbusDataUnit dataUnit);
signals:
    ///通知界面，有数据变化
    /// \brief signalValChanged
    /// \param signalVals
    ///
    void signalValChanged(QVariantList signalVals);

private:
    MyModbus* myModbus;
    DowInit* dowInit;
    QVariantList signalVals;
};

#endif // MAINBACKEND_H
