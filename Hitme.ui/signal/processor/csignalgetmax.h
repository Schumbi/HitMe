#ifndef CSIGNALGETMAX_H
#define CSIGNALGETMAX_H

#include <QObject>

#include "../cabstractprocessor.h"

namespace signal
{

class CSignalGetMax : public CAbstractProcessor
{

    Q_OBJECT

public:
    explicit CSignalGetMax ( CSignalProcessing *p );

signals:
    void maxValue ( QVector3D max );

    // CAbstractProcessor interface
protected:
    virtual void changeData ( data_t &data );
};

}

#endif // CSIGNALGETMAX_H
