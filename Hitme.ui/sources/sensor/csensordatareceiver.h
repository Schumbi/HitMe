#ifndef CSENSORDATAPROCESSOR_H
#define CSENSORDATAPROCESSOR_H

#include "cabstractdataprocessor.h"

class CSensorDataReceiver: public CAbstractNetworkProcessor {

    Q_OBJECT

public:
    CSensorDataReceiver (QObject *parent = nullptr);

    virtual bool processData (const QByteArray& data, CSensorStatus &toFill);

signals:
    void processedData (const CSensorData &data);

};


#endif // CSENSORDATAPROCESSOR_H
