#ifndef CSIGNALRECTIFIER_H
#define CSIGNALRECTIFIER_H

#include "../cabstractprocessor.h"

namespace signal
{

class CSignalRectifier : public  CAbstractProcessor
{

public:
    CSignalRectifier ( CSignalProcessing *parent = nullptr );

    // AbstractProcessor interface
protected:

    virtual void changeData ( data_t &data );
};

}
#endif // CSIGNALRECTIFIER_H
