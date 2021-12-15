#ifndef MAINBACKEND_H
#define MAINBACKEND_H

#include <QObject>
#include <QVariant>
#include "mymodbus.h"
#include "dowinit.h"
#include "signal_vals.h"
#include "experiment.h"
#include "infolist.h"
#pragma execution_character_set("utf-8")
using namespace std;
class MainBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString operName READ operName WRITE setOperName NOTIFY operNameChanged)
    Q_PROPERTY(QString exprimentName READ exprimentName WRITE setExprimentName NOTIFY exprimentNameChanged)
    Q_PROPERTY(bool willRec READ willRec WRITE setWillRec NOTIFY willRecChanged)
//    Q_PROPERTY(InfoListModel infoListModel READ infoListModel WRITE setInfoListModel NOTIFY infoListModelChanged)
public:
    explicit MainBackend(QObject *parent = nullptr);
    MainBackend(DowInit *dowInit,MyModbus *mymodbus,QObject *parent = nullptr);

public:
    Q_INVOKABLE void askSignalVals();
    Q_INVOKABLE QVariantList retSignalVals();
    void setMyModbus(MyModbus *myModbus);
    void setDowInit(DowInit *value);
    void setInfoListModel(InfoListModel& infoListModel);


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
    void addInfoList(QString info);
//    void recInfo_to_db(QString info);
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
        id_experiment=experiment.findLastExpriment_id_by_name_from_db(m_exprimentName);
        m_willRec = willRec;
        emit willRecChanged(m_willRec);
        if(m_willRec==true){
            emit makeInfo("开始记录！");
        }else{
            emit makeInfo("停止记录！");
        }

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

    void makeInfo(QString info);
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
    InfoListModel* m_infoListModel;
};

#endif // MAINBACKEND_H
