#include "csignalrectifier.h"

#include <cmath>

signal::CSignalRectifier::CSignalRectifier (signal::CSignalProcessing *parent)
    : CAbstractProcessor (parent)
{}

void signal::CSignalRectifier::changeData (data_t &data)
{
    double fac = p->conversionFactor();


    unsigned int n = data.size(); // number of samples
    double in_x;
    double in_y;
    double in_z;


    for (unsigned int ctr = 0; ctr < n; ctr++)
    {
        auto dat = data[n - ctr - 1];
        // load value
        in_x = dat.x() * fac;
        in_y = dat.y() * fac;
        in_z = dat.z() * fac;
        data[n - ctr - 1].setX (abs (
                                    sqrt (in_x * in_x +
                                          in_y * in_y +
                                          in_z * in_z)));
        data[n - ctr - 1].setY (-1);
        data[n - ctr - 1].setZ (-1);
    }

}
