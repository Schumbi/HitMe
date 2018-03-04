#include "cabstractcalculator.h"


CAbstractCalculator::CAbstractCalculator (QObject *parent) : QObject (parent)
{}

void CAbstractCalculator::calculateData (const CSensorData &raw)
{
    auto res = calculate (raw);
    emit finished (res);
}
