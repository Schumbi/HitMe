#include "cabstractprocessor.h"

#include <assert.h>

using namespace signal;

CAbstractProcessor::CAbstractProcessor (CSignalProcessing *p)
    : QObject (p),
      p (p)
{
    assert (p != nullptr);
}

CAbstractProcessor::~CAbstractProcessor()
{}

void CAbstractProcessor::process (data_t &data)
{
    changeData (data);
}
