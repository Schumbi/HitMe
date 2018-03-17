#include "caccstorage.h"

#include "caccdataconverter.h"

#include <cmath>
#include <QDebug>

constexpr int maxStorageSize = 1000 * 60 * 5;

CAccStorage::CAccStorage (QObject *parent) : QObject (parent)
{
    m_meanPeriod = 0;
    m_packetCtr = 0;
    m_maxdiff = 0;
    m_mindiff = 0;
    resetToZero();
}

void CAccStorage::processNewData (const CSensorData &newdata)
{
    auto start = newdata.startTime();
    auto end = newdata.endTime();
    auto total = newdata.size();
    double period = (end - start) / static_cast<double> (total);

    m_packetCtr++;
    m_meanPeriod += period;
    m_meanPeriod /= 2;


    double c = period - m_meanPeriod;
    m_maxdiff = qMax (m_maxdiff, c);
    m_mindiff = qMin (m_mindiff, c);

    for (int ctr = 0; ctr < total; ctr++)
    {
        if (m_storage.size() >= maxStorageSize)
        {
            m_storage.removeFirst();
        }

        QVector4D datum (newdata[ctr], start + (period * ctr));
        m_storage.append (datum);
    }

    // qDebug() << *this;
}

void CAccStorage::resetToZero()
{
    m_storage.reserve (maxStorageSize);

    for (int ctr = 0; ctr < maxStorageSize; ctr++)
    {
        m_storage.append (QVector4D (0, 0, 0, ctr));
    }
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

int CAccStorage::size() const
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

data_t CAccStorage::getLastValues (int count) const
{
    data_t res;

    if (m_storage.size() < count)
    {
        for (int ctr = 0; ctr < m_storage.size(); ctr++)
        {
            res.append (m_storage[ctr]);
        }

        return res;
    }

    res.reserve (count);
    int cnt = m_storage.size() - count;

    for (; cnt < m_storage.size(); cnt++)
    {
        res.append (m_storage[cnt]);
    }

    return res;
}

quint64 CAccStorage::addRawData (const QByteArray &data)
{
    CAccDataConverter::conv32_t conv32;
    CAccDataConverter::conv16_t conv16;

    CSensorData accData;
    // data[0] LSB
    // data[1]
    // data[2]
    // data[3] MSB time stamp begin
    conv32.val8x4[0] = data[0];
    conv32.val8x4[1] = data[1];
    conv32.val8x4[2] = data[2];
    conv32.val8x4[3] = data[3];
    accData.setStartTimestamp (conv32.val32x1);
    // data[0] LSB
    // data[1]
    // data[2]
    // data[3] MSB time stamp end
    conv32.val8x4[0] = data[4];
    conv32.val8x4[1] = data[5];
    conv32.val8x4[2] = data[6];
    conv32.val8x4[3] = data[7];
    accData.setEndTimestamp (conv32.val32x1);
    // data[4] LSB
    // data[5]
    // data[6]
    // data[7] MSB packet id (sensor)
    conv32.val8x4[0] = data[8];
    conv32.val8x4[1] = data[9];
    conv32.val8x4[2] = data[10];
    conv32.val8x4[3] = data[11];
    accData.setId (conv32.val32x1);

    // extract data
    for (int ctr = 12; ctr < (data.size() - 6); ctr += 6)
    {
        conv16.data8x2[0] = data[ctr + 0];
        conv16.data8x2[1] = data[ctr + 1];
        uint16_t rawx = conv16.data16x1;
        conv16.data8x2[0] = data[ctr + 2];
        conv16.data8x2[1] = data[ctr + 3];
        uint16_t rawy = conv16.data16x1;
        conv16.data8x2[0] = data[ctr + 4];
        conv16.data8x2[1] = data[ctr + 5];
        uint16_t rawz = conv16.data16x1;
        auto accValues = CAccDataConverter (rawx, rawy, rawz);
        accData.append (QVector3D (accValues.x(), accValues.y(), accValues.z()));
    }

    processNewData (accData);
    return packetCount();
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
