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
    Q_PROPERTY(QString operName READ operName WRITE setOperName NOTIFY operNameChanged)
public:
    explicit MainBackend(QObject *parent = nullptr);
    MainBackend(DowInit *dowInit,MyModbus *mymodbus,QObject *parent = nullptr);

public:
    Q_INVOKABLE void askSignalVals();
    Q_INVOKABLE QVariantList retSignalVals();
    void setMyModbus(MyModbus *myModbus);
    void setDowInit(DowInit *value);

    QString operName() const
    {
        return m_operName;
    }
    QString getOperName_from_db();
public slots:
    QVariantList getSignalVals(QModbusDataUnit dataUnit);

    void recordOperName_to_db(QString operName);
    void setOperName(QString operName)
    {
        if (m_operName == operName)
            return;

        m_operName = operName;
        emit operNameChanged(m_operName);
    }

signals:
    ///通知界面，有数据变化
    /// \brief signalValChanged
    /// \param signalVals
    ///
    void signalValChanged(QVariantList signalVals);

    void operNameChanged(QString operName);

private:
    MyModbus* myModbus;
    DowInit* dowInit;
    QVariantList signalVals;
    QString m_operName;
};

#endif // MAINBACKEND_H
