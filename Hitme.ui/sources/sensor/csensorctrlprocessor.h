#ifndef CSENSORCTRLPROCESSOR_H
#define CSENSORCTRLPROCESSOR_H

#include "cabstractdataprocessor.h"

class CSensorCtrlProcessor : public CAbstractNetworkProcessor {

    Q_OBJECT

public:
    CSensorCtrlProcessor (QObject *parent = nullptr);

    virtual bool processData (const QByteArray& data, CSensorStatus &toFill);

signals:
    void processedStatus (const CSensorStatus &status);

};

#endif // CSENSORCTRLPROCESSOR_H
