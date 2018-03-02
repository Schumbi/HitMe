#ifndef CSENSORDATAPROCESSOR_H
#define CSENSORDATAPROCESSOR_H

#include "../cabstractdataprocessor.h"

class CSensorDataProcessor : public CAbstractDataProcessor {

    Q_OBJECT

public:
    CSensorDataProcessor (QObject *parent = nullptr);

    virtual bool processData (const QByteArray& data, CSensorStatus &toFill);

signals:
    void processedData (CSensorData data);

};


#endif // CSENSORDATAPROCESSOR_H
