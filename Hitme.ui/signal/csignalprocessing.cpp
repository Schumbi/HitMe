#include "csignalprocessing.h"

#include <cmath>
#include <ccomplex>

#include <liquid/liquid.h>

using namespace signal;

CSignalProcessing::CSignalProcessing (QObject *parent) : QObject (parent)
{
    unsigned int order =   1;         // filter order
    float        fc    =   0.1f;      // cutoff frequency
    float        f0    =   0.0f;      // center frequency
    float        Ap    =   2.0f;      // pass-band ripple
    float        As    =  40.0f;      // stop-band attenuation

    liquid_iirdes_filtertype ftype  = LIQUID_IIRDES_ELLIP;
    liquid_iirdes_bandtype   btype  = LIQUID_IIRDES_HIGHPASS;
    liquid_iirdes_format     format = LIQUID_IIRDES_SOS;
    // design filter from prototype
    qx = iirfilt_rrrf_create_prototype (
             ftype, btype, format, order, fc, f0, Ap, As);
    qy = iirfilt_rrrf_create_prototype (
             ftype, btype, format, order, fc, f0, Ap, As);
    qz = iirfilt_rrrf_create_prototype (
             ftype, btype, format, order, fc, f0, Ap, As);

}

CSignalProcessing::~CSignalProcessing()
{
    iirfilt_rrrf_destroy (qx);
    iirfilt_rrrf_destroy (qy);
    iirfilt_rrrf_destroy (qz);
}

bool CSignalProcessing::process (data_t &data)
{
    unsigned int n     = data.size(); // number of samples
    float in_x;
    float ou_x;
    float in_y;
    float ou_y;
    float in_z;
    float ou_z;

    for (unsigned int ctr = 0; ctr < n; ctr++)
    {
        auto d = data[n - ctr - 1];
        // load value
        in_x = d.x();
        in_y = d.y();
        in_z = d.z();
        iirfilt_rrrf_execute (qx, in_x, &ou_x);
        iirfilt_rrrf_execute (qy, in_y, &ou_z);
        iirfilt_rrrf_execute (qz, in_z, &ou_z);
        data[n - ctr - 1].setX (ou_x);
        data[n - ctr - 1].setY (ou_y);
        data[n - ctr - 1].setZ (ou_z);
    }

    return true;
}


