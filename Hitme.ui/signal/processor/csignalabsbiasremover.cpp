#include "csignalabsbiasremover.h"

#include <cmath>

using namespace signal;

CSignalAbsBiasRemover::CSignalAbsBiasRemover (CSignalProcessing *parent) :
    CAbstractProcessor (parent)
{}

void CSignalAbsBiasRemover::changeData (data_t &data)
{
    auto bias = p->bias();

    for (int ctr = 0; ctr < data.size(); ctr++)
    {
        double x = data[ctr].x() - bias.x();
        double y = data[ctr].y() - bias.y();
        double z = data[ctr].z() - bias.z();
        data[ctr].setX (x);
        data[ctr].setY (y);
        data[ctr].setZ (z);
    }
}
