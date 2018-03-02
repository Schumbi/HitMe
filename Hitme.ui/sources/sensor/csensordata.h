#ifndef CSENSORDATA_H
#define CSENSORDATA_H

#include <QVector>
#include <QVector3D>

#include <QMetaType>

class CSensorData : public QVector<QVector3D> {

private:
    quint64 m_startTime;

public:
    CSensorData();
    CSensorData (const CSensorData &other);

    void setTimestamp (quint64 startTime);
    quint64 startTime();
};

Q_DECLARE_METATYPE (CSensorData);

#endif // CSENSORDATA_H
