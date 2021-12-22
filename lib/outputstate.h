#ifndef OUTPUTSTATE_H
#define OUTPUTSTATE_H

#include <QList>
#include <QString>







class OutPutState
{
public:
    OutPutState(QString outPutName,bool state);

    QString outPutName() const;
    void setOutPutName(const QString &outPutName);

    bool state() const;
    void setState(bool state);


private:
    QString m_outPutName;
    bool  m_state;
};


class OutPutStates
{

public:
    OutPutStates();
    void add(OutPutState outPutState);




    QList<OutPutState> member() const;

private:
    QList<OutPutState> m_member;
};
#endif // OUTPUTSTATE_H
