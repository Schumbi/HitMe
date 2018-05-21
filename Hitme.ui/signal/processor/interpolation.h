#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QPointF>

class Interpolation_impl;

class Interpolation {

public:
    Interpolation (QPointF p1, QPointF p2, QPointF p3, QPointF p4);
    virtual ~Interpolation();

    double y (double x);

private:
    Interpolation_impl *d;
};

#endif // INTERPOLATION_H
