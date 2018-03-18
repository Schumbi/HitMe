#include "csignalprocessing.h"

#include <cmath>
#include <ccomplex>

#include <liquid/liquid.h>

using namespace signal;

CSignalProcessing::CSignalProcessing (QObject *parent) : QObject (parent)
{}

bool CSignalProcessing::process (data_t &data, double &fac)
{
    unsigned int n     = data.size(); // number of samples
    double in_x;
    double in_y;
    double in_z;

    for (unsigned int ctr = 0; ctr < n; ctr++)
    {
        auto d = data[n - ctr - 1];
        // load value
        in_x = d.x() * fac;
        in_y = d.y() * fac;
        in_z = d.z() * fac;
        data[n - ctr - 1].setX (sqrt (in_x * in_x + in_y * in_y + in_z * in_z));
        data[n - ctr - 1].setY (-1);
        data[n - ctr - 1].setZ (-1);
    }

    return true;
}


