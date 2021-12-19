#ifndef SETPARABACKEND_H
#define SETPARABACKEND_H

#include "dowinit.h"
#include "getplcval.h"
#include "para_with_plc.h"
#include "syspara.h"

#include <QObject>
#pragma execution_character_set("utf-8")

class SetParaBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int recordRecycle_s READ recordRecycle_s WRITE setRecordRecycle_s NOTIFY recordCycle_sChanged)
    Q_PROPERTY(int realTimeCurve_flashcycle_s READ realTimeCurve_flashcycle_s WRITE setRealTimeCurve_flashcycle_s NOTIFY realTimeCurve_flashcycle_sChanged)
    Q_PROPERTY(int realTimeCurve_time_s READ realTimeCurve_time_s WRITE setRealTimeCurve_time_s NOTIFY realTimeCurve_time_sChanged)
    Q_PROPERTY(int askPlc_cycle_ms READ askPlc_cycle_ms WRITE setAskPlc_cycle_ms NOTIFY askPlc_cycle_msChanged)
    Q_PROPERTY(QVariantList para_plc READ para_plc WRITE setPara_plc NOTIFY para_plcChanged)

private:
    SysPara sysPara;
    int m_recordCycle_s;
    int m_realTimeCurve_flashcycle_s;

    int m_realTimeCurve_time_s;


    int m_askPlc_cycle_ms;

    QVariantList m_para_plc;

    DowInit *dowInit;
    GetPlcVal *getPlcVal;

public:
    explicit SetParaBackend(QObject *parent = nullptr);
    SetParaBackend(DowInit *dowInit,GetPlcVal *getPlcVal,QObject *parent = nullptr);
    Q_INVOKABLE QVariantList readPara();
    Q_INVOKABLE void setPlcPara(QVariantList inputVal);
    int recordRecycle_s()
    {

        m_recordCycle_s=sysPara.getRecordRecycle_s_from_db();
        return m_recordCycle_s;
    }

    int realTimeCurve_flashcycle_s()
    {
//        SysPara sysPara;
        m_realTimeCurve_flashcycle_s=sysPara.getRealTimeCureve_flashcycle_s_from_db();
        return m_realTimeCurve_flashcycle_s;

    }


    int realTimeCurve_time_s()
    {
        m_realTimeCurve_time_s=sysPara.getRealTimeCurve_time_s_from_db();
        return m_realTimeCurve_time_s;
    }

    int askPlc_cycle_ms()
    {
        m_askPlc_cycle_ms=sysPara.getAskPlc_cycle_ms_from_db();
        return m_askPlc_cycle_ms;
    }

    QVariantList para_plc()
    {
        m_para_plc=getPlcVal->getParaVals();
        return m_para_plc;
    }

public slots:
    void setRealTimeCurve_flashcycle_s(int realTimeCurve_flashcycle_s);
    void getParaFromPlc(QVariantList paraFromPlc);
    void setRecordRecycle_s(int recordCycle_s)
    {
        if (m_recordCycle_s == recordCycle_s)
            return;

        m_recordCycle_s = recordCycle_s;
        emit recordCycle_sChanged(m_recordCycle_s);
    }

    void recordRecycle_to_db(int recordCycle_s);
    void realTimeCurve_flashcycle_s_to_db(int realTimeCurve_flashcycle_s);
    void realTimeCurve_time_s_to_db(int realTimeCurve_time_s);
    void askPlc_cycle_ms_to_db(int askPlc_cycle_ms);
    void setRealTimeCurve_time_s(int realTimeCurve_time_s)
    {
        if (m_realTimeCurve_time_s == realTimeCurve_time_s)
            return;

        m_realTimeCurve_time_s = realTimeCurve_time_s;
        emit realTimeCurve_time_sChanged(m_realTimeCurve_time_s);
    }

    void setAskPlc_cycle_ms(int askPlc_cycle_ms)
    {
        if (m_askPlc_cycle_ms == askPlc_cycle_ms)
            return;

        m_askPlc_cycle_ms = askPlc_cycle_ms;
        emit askPlc_cycle_msChanged(m_askPlc_cycle_ms);
    }

    void setPara_plc(QVariantList para_plc)
    {
        if (m_para_plc == para_plc)
            return;

        m_para_plc = para_plc;
        emit para_plcChanged(m_para_plc);
    }

signals:

    void recordCycle_sChanged(int recordCycle_s);
    void realTimeCurve_flashcycle_sChanged(int realTimeCurve_flashcycle_s);
    void realTimeCurve_time_sChanged(int realTimeCurve_time_s);
    void askPlc_cycle_msChanged(int askPlc_cycle_ms);
    void para_plcChanged(QVariantList para_plc);
    void sendParaFromPlcToView(QVariantList paraFromPlc);

};

#endif // SETPARABACKEND_H
