#ifndef SETPARABACKEND_H
#define SETPARABACKEND_H

#include "syspara.h"

#include <QObject>
#pragma execution_character_set("utf-8")

class SetParaBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int recordRecycle_s READ recordRecycle_s WRITE setRecordRecycle_s NOTIFY recordCycle_sChanged)
    int m_recordCycle_s;

public:
    explicit SetParaBackend(QObject *parent = nullptr);

    int recordRecycle_s()
    {
        SysPara sysPara;
        m_recordCycle_s=sysPara.getRecordRecycle_s_from_db();
        return m_recordCycle_s;
    }

public slots:
    void setRecordRecycle_s(int recordCycle_s)
    {
        if (m_recordCycle_s == recordCycle_s)
            return;

        m_recordCycle_s = recordCycle_s;
        emit recordCycle_sChanged(m_recordCycle_s);
    }

    void recordRecycle_to_db(int recordCycle_s);

signals:

    void recordCycle_sChanged(int recordCycle_s);
};

#endif // SETPARABACKEND_H
