﻿#ifndef MAINBACKEND_H
#define MAINBACKEND_H

#include <QObject>
#include <QVariant>
#include "mymodbus.h"
#include "dowinit.h"
#include "signal_vals.h"
#include "experiment.h"
#pragma execution_character_set("utf-8")
using namespace std;
class MainBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString operName READ operName WRITE setOperName NOTIFY operNameChanged)
    Q_PROPERTY(QString exprimentName READ exprimentName WRITE setExprimentName NOTIFY exprimentNameChanged)
    Q_PROPERTY(bool willRec READ willRec WRITE setWillRec NOTIFY willRecChanged)
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

    QString exprimentName() const
    {
        return m_exprimentName;
    }

    bool willRec() const
    {
        return m_willRec;
    }

public slots:
    QVariantList getSignalVals(QModbusDataUnit dataUnit);
    void recVal_to_db();
    void recordOperName_to_db(QString operName);
    void recordExprimentName_to_db(QString csExprimentName);
    void setOperName(QString operName)
    {
        if (m_operName == operName)
            return;

        m_operName = operName;
        emit operNameChanged(m_operName);
    }

    void setExprimentName(QString exprimentName)
    {
        if (m_exprimentName == exprimentName)
            return;

        m_exprimentName = exprimentName;
        emit exprimentNameChanged(m_exprimentName);
    }

    void setWillRec(bool willRec)
    {
        if (m_willRec == willRec)
            return;

        m_willRec = willRec;
        emit willRecChanged(m_willRec);
    }

signals:
    ///通知界面，有数据变化
    /// \brief signalValChanged
    /// \param signalVals
    ///
    void signalValChanged(QVariantList signalVals);

    void operNameChanged(QString operName);

    void exprimentNameChanged(QString exprimentName);

    void willRecChanged(bool willRec);

private:
    MyModbus* myModbus;
    DowInit* dowInit;
    QTimer *timer;
    QVariantList signalVals;
    QString m_operName;
    QString m_exprimentName;
    bool m_willRec;
    Signal_vals signal_vals;
    Experiment experiment;
    int id_experiment;
};

#endif // MAINBACKEND_H
