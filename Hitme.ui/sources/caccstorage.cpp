#include "caccstorage.h"

#include <cmath>
#include <QDebug>

CAccStorage::CAccStorage (QObject *parent) : QObject (parent)
{}

void CAccStorage::append (const CSensorData &newdata)
{
    auto start = newdata.startTime();
    auto end = newdata.endTime();
    auto total = newdata.size();
    double period = (end - start) / static_cast<double> (total);

    if (m_storage.size() == 0)
    {
        m_meanPeriod = period;
        m_mindiff = 0.0;
        m_maxdiff = 0.0;
    }
    else
    {
        double newPeriod = period;

        if (newPeriod > m_meanPeriod)
        {
            double c = newPeriod - m_meanPeriod;
            m_maxdiff = qMax (m_maxdiff, c);
        }

        if (newPeriod < m_meanPeriod)
        {
            double c = newPeriod - m_meanPeriod;
            m_mindiff = qMin (m_mindiff, c);
        }

        m_meanPeriod =  newPeriod;
    }

    for (int ctr = 0; ctr < total; ctr++)
    {
        QVector4D datum (newdata[ctr], start + (period * ctr));
        m_storage.append (datum);
    }

    qDebug() << *this;
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

QDebug operator<< (QDebug dbg, const CAccStorage &data)
{
    dbg.nospace() << "CAccStorage(): timing: "
                  << " mean:    " << data.meanPeriod()
                  << " mindiff: " << data.mindiff()
                  << " maxdiff: " << data.maxdiff()
                  << " size   : " << data.size();
    dbg.maybeSpace();
    return dbg;
}
