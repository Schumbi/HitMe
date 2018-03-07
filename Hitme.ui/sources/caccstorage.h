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

public:
    explicit CAccStorage (QObject *parent = nullptr);

    data_t get (uint32_t startTime, uint32_t endTime);

    double meanPeriod() const;
    double maxdiff() const;
    double mindiff() const;
    double size() const;
    quint64 packetCount() const;
    data_t storage() const;

signals:
    void gotPacket (quint64 packetCtr);

public slots:
    void append (const CSensorData& newdata);
};

QDebug operator<< (QDebug dbg, const CAccStorage &data);

#endif // CACCSTORAGE_H
