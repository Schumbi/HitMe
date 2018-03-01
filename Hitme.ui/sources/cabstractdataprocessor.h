#ifndef CDATAPROCESSOR_H
#define CDATAPROCESSOR_H

#include <QObject>
#include <QNetworkDatagram>

#include "csensorstatus.h"


class CAbstractDataProcessor : public QObject {

    Q_OBJECT

public:
    explicit CAbstractDataProcessor (QObject *parent = nullptr);

    virtual bool processData (const QByteArray&data, CSensorStatus &toFill) = 0;

signals:
    void processingFinished ();

public slots:
    virtual void processDatagram (const QNetworkDatagram &data) = 0;
};

#endif // CDATAPROCESSOR_H
