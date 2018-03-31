#include "csignalprocessing.h"
#include "csignalprocessingprivate.h"

using namespace signal;

double CSignalProcessing::conversionFactor() const
{
    return d->conversionFactor();
}

void CSignalProcessing::setConversionFactor(double conversionFactor)
{
    d->setConversionFactor(conversionFactor);
}

QVector3D CSignalProcessing::bias()
{
    return d->bias();
}

QVector3D CSignalProcessing::maxValue()
{
    return d->maxValue();
}

CSignalProcessing::CSignalProcessing(QObject *parent) :
    QObject(parent),
    d(new CSignalProcessingPrivate(this))
{}

CSignalProcessing::~CSignalProcessing()
{
    if (d != nullptr) {
        delete d;
    }
}

void CSignalProcessing::process(data_t &data)
{
    d->process(data);
}

void CSignalProcessing::setCalibrating(bool state)
{
    d->setCalibrating(state);
}


