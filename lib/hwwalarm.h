#ifndef HWWALARM_H
#define HWWALARM_H
#pragma execution_character_set("utf-8")
#include "getplcval.h"

#include <QObject>

enum class AlarmState
{
    generate,
    handled,
    none
};
class HwwAlarm : public QObject
{
    Q_OBJECT
public:
    explicit HwwAlarm(QString content,AlarmState state,QObject *parent = nullptr);

    QString content() const;
    void setContent(const QString &content);

    AlarmState state() const;
    void setState(const AlarmState &state);


private:
    QString m_content;
    AlarmState m_state;
};
//#pragma execution_character_set("utf-8")
class HwwAlarms:public QObject
{
    Q_OBJECT
public slots:
    void getAlarm_form_plc_signal(int prevous_alarms,int just_alarms);
public:
    HwwAlarms(GetPlcVal* getPlcVal);


    QList<QString> getAlarmsInfo() const;

    QList<HwwAlarm*> getInit_alarms() const;

signals:
    void makeAlarmInfo(QString info);
private:
    void append(HwwAlarm *hwwAlarm);
    GetPlcVal *getPlcVal;
    QList<QString> m_alarmsInfo;
    QList<HwwAlarm*>m_init_alarms;
    QTextCodec *codec;
};
#endif // HWWALARM_H
