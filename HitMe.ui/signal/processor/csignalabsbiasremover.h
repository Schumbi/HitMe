#ifndef CSIGNALABSBIASREMOVER_H
#define CSIGNALABSBIASREMOVER_H

#include <QObject>
#include "../cabstractprocessor.h"

namespace signal
{

class CSignalAbsBiasRemover : public CAbstractProcessor
{

    Q_OBJECT

public:
    explicit CSignalAbsBiasRemover ( CSignalProcessing *parent = nullptr );

signals:

public slots:

    // AbstractProcessor interface
protected:
    virtual void changeData ( data_t &data );
};

}

#endif // CSIGNALABSBIASREMOVER_H
