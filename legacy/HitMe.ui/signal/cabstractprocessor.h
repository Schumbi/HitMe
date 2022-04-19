#ifndef ABSTRACTPROCESSOR_H
#define ABSTRACTPROCESSOR_H

#include <QObject>
#include <csignalprocessing.h>

namespace signal
{

class CAbstractProcessor : public QObject
{
    Q_OBJECT

protected:
    CSignalProcessing *p;

    virtual void changeData ( data_t &data ) = 0;

public:
    explicit CAbstractProcessor ( CSignalProcessing *p = nullptr );
    virtual ~CAbstractProcessor();

    void process ( data_t &data );

};

}

#endif // ABSTRACTPROCESSOR_H
