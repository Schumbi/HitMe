#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QPointF>
#include <QString>

class Interpolation_impl;

class CCubicFunctionSolver {

public:
    CCubicFunctionSolver (QPointF p1, QPointF p2, QPointF p3, QPointF p4);
    virtual ~CCubicFunctionSolver();

    double y (double x);

    QString deb_print();

private:
    Interpolation_impl *d;
};

#endif // INTERPOLATION_H
