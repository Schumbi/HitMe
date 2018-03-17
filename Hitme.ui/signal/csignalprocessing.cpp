#include "csignalprocessing.h"

#include <cmath>
#include <ccomplex>

#include <liquid/liquid.h>

using namespace signal;

CSignalProcessing::CSignalProcessing (QObject *parent) : QObject (parent)
{
    unsigned int order =   8;         // filter order
    float        fc    =   0.01f;      // cutoff frequency
    float        f0    =   0.0f;      // center frequency
    float        Ap    =   1.0f;      // pass-band ripple
    float        As    =  40.0f;      // stop-band attenuation

    liquid_iirdes_filtertype ftype  = LIQUID_IIRDES_ELLIP;
    liquid_iirdes_bandtype   btype  = LIQUID_IIRDES_HIGHPASS;
    liquid_iirdes_format     format = LIQUID_IIRDES_SOS;
    // design filter from prototype
    q = iirfilt_rrrf_create_prototype (
            ftype, btype, format, order, fc, f0, Ap, As);

}

CSignalProcessing::~CSignalProcessing()
{
    iirfilt_rrrf_destroy (q);
}

bool CSignalProcessing::process (data_t &data)
{
    unsigned int n     = data.size(); // number of samples
    float cx[n];
    float cy[n];

    for (unsigned int ctr = 0; ctr < n; ctr++)
    {
        // load value
        cx[ctr] = data[ctr].z();
        iirfilt_rrrf_execute (q, cx[ctr], &cy[ctr]);
        data[ctr].setZ (cy[ctr]);
    }

    return true;
}


