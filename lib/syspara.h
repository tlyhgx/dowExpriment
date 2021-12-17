#ifndef SYSPARA_H
#define SYSPARA_H

#include <QObject>

class SysPara : public QObject
{
    Q_OBJECT
public:
    explicit SysPara(QObject *parent = nullptr);
    int getRecordRecycle_s_from_db();
    void setRecordCycle_s_to_db(int recordCycle_s);
    int getRealTimeCureve_flashcycle_s_from_db();
    void setRealTimeCureve_flashcycle_s_to_db(int realTimeCurve_flashcycle_s);
    int getRealTimeCurve_time_s_from_db();
    void setRealTimeCurve_time_s_to_db(int realTimeCurve_time_s);
    int getAskPlc_cycle_ms_from_db();
    void setAskPlc_cycle_ms_to_db(int askPlc_cycle_ms);
signals:

};

#endif // SYSPARA_H
