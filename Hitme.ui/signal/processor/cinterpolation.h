#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QPointF>

class Interpolation_impl;

class CInterpolation {

public:
    CInterpolation (QPointF p1, QPointF p2, QPointF p3, QPointF p4);
    virtual ~CInterpolation();

    double y (double x);

private:
    Interpolation_impl *d;
};

#endif // INTERPOLATION_H
