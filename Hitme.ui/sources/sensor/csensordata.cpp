#include "csensordata.h"


quint64 CSensorData::startTime()
{
    return m_startTime;
}

CSensorData::CSensorData()
    : QVector<QVector3D> (), m_startTime (0)
{

}

CSensorData::CSensorData (const CSensorData &other)
    : QVector<QVector3D> (other)
{
    m_startTime = other.m_startTime;
}

void CSensorData::setTimestamp (quint64 startTime)
{
    m_startTime = startTime;
}
