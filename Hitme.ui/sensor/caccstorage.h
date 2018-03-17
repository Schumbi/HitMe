#ifndef CACCSTORAGE_H
#define CACCSTORAGE_H

#include <csensordata.h>
#include <QObject>

#include <QList>
#include <QVector4D>

typedef QList<QVector4D> data_t ;

class CAccStorage : public QObject {

    Q_OBJECT

    data_t m_storage;

    quint64 m_packetCtr;
    double m_meanPeriod;
    double m_maxdiff;
    double m_mindiff;

    void processNewData (const CSensorData& newdata);


public:
    explicit CAccStorage (QObject *parent = nullptr);

    void resetToZero();
    quint64 addRawData (const QByteArray& newdata);

    double meanPeriod() const;
    double maxdiff() const;
    double mindiff() const;
    int size() const;
    quint64 packetCount() const;
    data_t storage() const;
    data_t getLastValues (int count) const;


};

QDebug operator<< (QDebug dbg, const CAccStorage &data);

#endif // CACCSTORAGE_H
