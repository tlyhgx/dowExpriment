#ifndef MAINBACKEND_H
#define MAINBACKEND_H

#include <QObject>
#include <QVariant>
//#include "mymodbus.h"
#include "dowinit.h"
#include "signal_vals.h"
#include "experiment.h"
#include "infolist.h"
#include "getplcval.h"
#include "hwwalarm.h"
#include "db_oper.h"
#pragma execution_character_set("utf-8")
using namespace std;
class MainBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString operName READ operName WRITE setOperName NOTIFY operNameChanged)
    Q_PROPERTY(QVariantList list_operName READ list_operName  NOTIFY list_operNameChanged)
    Q_PROPERTY(QString exprimentName READ exprimentName WRITE setExprimentName NOTIFY exprimentNameChanged)
    Q_PROPERTY(bool willRec READ willRec WRITE setWillRec NOTIFY willRecChanged)

public:
    explicit MainBackend(QObject *parent = nullptr);
    MainBackend(DowInit *dowInit,GetPlcVal *getPlcVal,QObject *parent = nullptr);

public:
//    Q_INVOKABLE void askSignalVals();
    Q_INVOKABLE void startSys();
    Q_INVOKABLE void stopSys();


    void setInfoListModel(InfoListModel& infoListModel);
    void setAlarmsInfo(HwwAlarms& alarmsInfo);

    QString operName() const
    {
        return m_operName;
    }

    QVariantList list_operName()
    {
        QVariantList operNames;
        DB_oper db_oper;
        operNames=db_oper.getOperNames();
        return operNames;
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
    void sendOtherSignalVals_to_view(QVariantList otherSignalVals);
    void sendTempSignalVals_to_view(QVariantList tempSignalVals);
    void send_OutPutState_to_view(QVariantList outPutStateVals );
    void addInfoList(QString info);
    void recVal_to_db();
    void recordOperName_to_db(QString operName);
    void recordExprimentName_to_db(QString csExprimentName);
    void eixtSys();
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

    void tempSignalValChanged(QVariantList tempSignalVals);
    void otherSignalValChanged(QVariantList otherSignalVals);
    void outPutStateChanged(QVariantList outPutStateVals);
    void operNameChanged(QString operName);
    void list_operNameChanged();

    void exprimentNameChanged(QString exprimentName);

    void willRecChanged(bool willRec);

    void makeInfo(QString info);
private:
    GetPlcVal *getPlcVal;
    DowInit* dowInit;
    QTimer *timer;
    QVariantList otherSignalVals;
    QVariantList tempSignalVals;
    QString m_operName;
    QString m_exprimentName;
    bool m_willRec=false;
    Signal_vals signal_vals;
    Experiment experiment;
    int id_experiment;
    InfoListModel* m_infoListModel;
    HwwAlarms* m_alarmsInfo;
};

#endif // MAINBACKEND_H
