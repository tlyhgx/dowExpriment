#include "outputstate.h"



OutPutState::OutPutState(QString outPutName, bool state)
    :m_outPutName(outPutName),m_state(state)
{

}

QString OutPutState::outPutName() const
{
    return m_outPutName;
}

void OutPutState::setOutPutName(const QString &outPutName)
{
    m_outPutName = outPutName;
}

bool OutPutState::state() const
{
    return m_state;
}

void OutPutState::setState(bool state)
{
    m_state = state;
}

OutPutStates::OutPutStates()
{

}

void OutPutStates::add(OutPutState outPutState)
{
    m_member<<outPutState;
}


QList<OutPutState> OutPutStates::member() const
{
    return m_member;
}



