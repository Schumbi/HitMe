#ifndef CSENSORCTRLPROCESSOR_H
#define CSENSORCTRLPROCESSOR_H

#include "cabstractdataprocessor.h"

class CSensorCtrlTransceiver : public CAbstractNetworkProcessor {

    Q_OBJECT

public:
    CSensorCtrlTransceiver (QObject *parent = nullptr);

    virtual bool processData (const QByteArray& data, CSensorStatus &toFill);

signals:
    void processedStatus (const CSensorStatus &status);

};

#endif // CSENSORCTRLPROCESSOR_H
