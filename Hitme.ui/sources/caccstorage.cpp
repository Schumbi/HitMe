#include "caccstorage.h"

#include <cmath>
#include <QDebug>

CAccStorage::CAccStorage (QObject *parent) : QObject (parent)
{
    m_meanPeriod = 0;
    m_packetCtr = 0;
    m_maxdiff = 0;
    m_mindiff = 0;
}

void CAccStorage::append (const CSensorData &newdata)
{
    auto start = newdata.startTime();
    auto end = newdata.endTime();
    auto total = newdata.size();
    double period = (end - start) / static_cast<double> (total);

    m_packetCtr++;
    m_meanPeriod += period;

    if (m_packetCtr > 1)
    {
        m_meanPeriod /= 2;
    }

    if (m_packetCtr <= 50)
    {
        m_mindiff = 0.0;
        m_maxdiff = 0.0;
    }
    else
    {
        double c = period - m_meanPeriod;
        m_maxdiff = qMax (m_maxdiff, c);
        m_mindiff = qMin (m_mindiff, c);
    }

    for (int ctr = 0; ctr < total; ctr++)
    {
        QVector4D datum (newdata[ctr], start + (period * ctr));
        m_storage.append (datum);
    }

    // qDebug() << *this;
    emit gotPacket (m_packetCtr - 1);
}

data_t CAccStorage::get (uint32_t startTime, uint32_t endTime)
{
    data_t ret;

    for (int ctr = 0; ctr < m_storage.size(); ctr++)
    {
        auto pos = m_storage[ctr].w();

        if ( pos >= startTime )
        {
            if (pos < endTime)
            {
                ret.append (m_storage[ctr]);
            }
            else
            {
                break;
            }
        }
    }

    return ret;
}

double CAccStorage::meanPeriod() const
{
    return m_meanPeriod;
}

double CAccStorage::maxdiff() const
{
    return m_maxdiff;
}

double CAccStorage::mindiff() const
{
    return  m_mindiff;
}

double CAccStorage::size() const
{
    return m_storage.size();
}

quint64 CAccStorage::packetCount() const
{
    return m_packetCtr;
}

data_t CAccStorage::storage() const
{
    return m_storage;
}

QDebug operator<< (QDebug dbg, const CAccStorage &data)
{
    dbg.nospace() << "CAccStorage(): timing: "
                  << " mean: " << data.meanPeriod()
                  << " mindiff: " << data.mindiff()
                  << " maxdiff: " << data.maxdiff()
                  << " size   : " << data.size()
                  << " pcnt   :" << data.packetCount();
    dbg.maybeSpace();
    return dbg;
}
