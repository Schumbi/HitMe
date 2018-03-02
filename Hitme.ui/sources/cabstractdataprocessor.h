#ifndef CDATAPROCESSOR_H
#define CDATAPROCESSOR_H

#include <QObject>
#include <QNetworkDatagram>

#include "sensor/csensordata.h"
#include "sensor/csensorstatus.h"


class CAbstractDataProcessor : public QObject {

    Q_OBJECT

    CSensorStatus m_sensorstatus;

public:
    explicit CAbstractDataProcessor (QObject *parent = nullptr);

    CSensorStatus sensorStatus();

    virtual bool processData (const QByteArray&data, CSensorStatus &toFill) = 0;

signals:
    void processingFinished ();

public slots:
    virtual void processDatagram (const QNetworkDatagram &data);
};

#endif // CDATAPROCESSOR_H
