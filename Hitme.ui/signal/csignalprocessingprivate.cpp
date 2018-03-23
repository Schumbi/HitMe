#include "csignalprocessingprivate.h"
#include "csignalprocessing.h"

#include "cabstractprocessor.h"

#include "processor/csignalabsbiasremover.h"
#include "processor/csignalrectifier.h"

#include <math.h>

using namespace signal;

QVector3D mean (const QVector<QVector3D> &in)
{
    int size = in.size();
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    foreach (auto s, in)
    {
        x += s.x();
        y += s.y();
        z += s.z();
    }

    x /= static_cast<double> (size);
    y /= static_cast<double> (size);
    z /= static_cast<double> (size);
    return QVector3D (x, y, z);
}

bool CSignalProcessingPrivate::isCalibrating() const
{
    return m_isCalibrating;
}

QVector3D CSignalProcessingPrivate::bias() const
{
    return m_bias;
}

void CSignalProcessingPrivate::calibrate (const data_t &data)
{
    foreach (auto s, data)
    {
        tempStorage.append (QVector3D (s.x(), s.y(), s.z()));

        if (tempStorage.size() > maxTempStorage)
        {
            int diff = tempStorage.size() - maxTempStorage;
            tempStorage.remove (0, diff);
        }
    }

    m_bias = mean (tempStorage);

    emit p->calibrated (m_bias);
}

double CSignalProcessingPrivate::conversionFactor() const
{
    return m_conversionFactor;
}

void CSignalProcessingPrivate::setConversionFactor (double conversionFactor)
{
    m_conversionFactor = conversionFactor;
}

CSignalProcessingPrivate::CSignalProcessingPrivate (CSignalProcessing *p)
    : QObject (p), p (p),
      m_bias (QVector3D (0, 0, 0)),
      m_isCalibrating (false),
      m_conversionFactor (1.0)
{
    procList.append (new CSignalAbsBiasRemover (p));
    procList.append (new CSignalRectifier (p));
}

CSignalProcessingPrivate::~CSignalProcessingPrivate()
{
    foreach (auto s, procList)
    {
        delete s;
    }
}

void CSignalProcessingPrivate::process (data_t &data)
{
    // calibrateing mode
    if (this->m_isCalibrating)
    {
        calibrate (data);
        return;
    }

    // process mode
    for (int ctr = 0; ctr < procList.size(); ctr++)
    {
        procList[ctr]->process (data);
    }
}

void CSignalProcessingPrivate::setCalibrating (bool isCalibrating)
{
    this->m_isCalibrating = isCalibrating;

    if (isCalibrating == false)
    {
        this->tempStorage.clear();
        this->tempStorage.squeeze();
    }
    else
    {
        this->tempStorage.reserve (maxTempStorage);
    }
}
