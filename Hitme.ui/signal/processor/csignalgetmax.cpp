#include "csignalgetmax.h"

using namespace signal;

CSignalGetMax::CSignalGetMax(CSignalProcessing *p)
    : CAbstractProcessor(p)
{}

void signal::CSignalGetMax::changeData(data_t &data)
{
    double maxx = 0.0;
    double maxy = 0.0;
    double maxz = 0.0;

    for (int ctr = 0; ctr < data.size(); ctr++) {
        maxx = qMax<double> (data[ctr].x(), maxx);
        maxy = qMax<double> (data[ctr].y(), maxy);
        maxz = qMax<double> (data[ctr].z(), maxz);
    }

    emit maxValue(QVector3D(maxx, maxy, maxz));
}
