#ifndef CSENSORCTRLPROCESSOR_H
#define CSENSORCTRLPROCESSOR_H

#include "cabstractdataprocessor.h"


class CSensorCtrlProcessor : public CAbstractDataProcessor {

    Q_OBJECT

public:
    CSensorCtrlProcessor (QObject *parent = nullptr);

    virtual bool processData (const QByteArray&data, CSensorStatus &toFill);

signals:
    void processedStatus (CSensorStatus status);

public slots:
    virtual void processDatagram (const QNetworkDatagram &netData);
};

#endif // CSENSORCTRLPROCESSOR_H
