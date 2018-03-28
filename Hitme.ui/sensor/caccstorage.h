#ifndef CACCSTORAGE_H
#define CACCSTORAGE_H

#include <csensordata.h>
#include <QObject>

#include <QVector>
#include <QVector4D>

typedef QVector<QVector4D> data_t ;

class CAccStorage : public QObject {

    Q_OBJECT

    data_t m_storage;

    quint64 m_packetCtr;
    double m_meanPeriod;
    double m_maxdiff;
    double m_mindiff;

    unsigned int m_lastTime;
    unsigned int m_pkgtimeDiff;
    unsigned int m_pCtrDiff;
    unsigned int m_samplingFrequ;
    unsigned int m_maxmeasurementSamples;

    void processNewData (const CSensorData& newdata);

public:
    explicit CAccStorage (QObject *parent = nullptr,
                          int maxSamplingTime_sec = 20,
                          int fs = 1000);

    void resetToZero();
    quint32 addRawData (const QByteArray& newdata);

    double meanPeriod() const;
    double maxdiff() const;
    double mindiff() const;
    int size() const;
    quint64 packetCount() const;
    data_t storage() const;
    data_t getLastValues (int count) const;


    unsigned int getMaxmeasurementtime_Sec() const;
    void setMaxmeasurementtime_Sec (unsigned int maxmeasurementtime_Sec);
    unsigned int getFs() const;
    void setFs (unsigned int period);
    unsigned int getPkgtimeDiff() const;
    void setPkgtimeDiff (unsigned int pkgtimeDiff);
    unsigned int getPCtrDiff() const;
};

QDebug operator<< (QDebug dbg, const CAccStorage &data);

#endif // CACCSTORAGE_H
