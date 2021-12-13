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
signals:

};

#endif // SYSPARA_H
