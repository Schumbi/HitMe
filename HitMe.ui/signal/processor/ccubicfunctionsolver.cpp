#include<QPointF>
#include <cmath>

#include "ccubicfunctionsolver.h"

class Interpolation_impl {
    /* calculated with maxima
     * [a,b,c,d] = solve([
        y_1 = a*x_1^3 + b*x_1^2 + c*x_1 + d,
        y_2 = a*x_2^3 + b*x_2^2 + c*x_2 + d,
        y_3 = a*x_3^3 + b*x_3^2 + c*x_3 + d,
        y_4 = a*x_4^3 + b*x_4^2 + c*x_4 + d],[a,b,c,d]);
    */
    double get_a (QPointF p1, QPointF p2, QPointF p3, QPointF p4)
    {
        double x_1 = p1.x();
        double y_1 = p1.y();
        double x_2 = p2.x();
        double y_2 = p2.y();
        double x_3 = p3.x();
        double y_3 = p3.y();
        double x_4 = p4.x();
        double y_4 = p4.y();

        double a = (x_1 * (pow (x_2, 2) * (y_4 - y_3)
                           - pow (x_3, 2) * y_4
                           + pow (x_4, 2) * y_3
                           + (pow (x_3, 2) - pow (x_4, 2) ) * y_2)
                    + x_2 * (pow (x_3, 2) * y_4 - pow (x_4, 2) * y_3)
                    + pow (x_1, 2) * (x_3 * y_4 + x_2 * (y_3 - y_4)
                                      - x_4 * y_3 + (x_4 - x_3) * y_2)
                    + pow (x_2, 2) * (x_4 * y_3 - x_3 * y_4)
                    + (x_3 * pow (x_4, 2) - pow (x_3, 2) * x_4) * y_2
                    + (x_2 * (pow (x_4, 2) - pow (x_3, 2))
                       - x_3 * pow (x_4, 2) + pow (x_3, 2) * x_4
                       + pow (x_2, 2) * (x_3 - x_4)) * y_1)
                   / (x_1 * (pow (x_2, 2) * (pow (x_4, 3) - pow (x_3, 3))
                             - pow (x_3, 2) * pow (x_4, 3)
                             + pow (x_3, 3) * pow (x_4, 2)
                             + pow (x_2, 3) * (pow (x_3, 2) - pow (x_4, 2)))
                      + x_2 * (pow (x_3, 2) * pow (x_4, 3)
                               - pow (x_3, 3) * pow (x_4, 2))
                      + pow (x_1, 2) * (x_3 * pow (x_4, 3)
                                        + x_2 * (pow (x_3, 3) - pow (x_4, 3))
                                        + pow (x_2, 3) * (x_4 - x_3)
                                        - pow (x_3, 3) * x_4)
                      + pow (x_2, 2) * (pow (x_3, 3) * x_4 - x_3 * pow (x_4, 3))
                      + pow (x_1, 3) * (x_2 * (pow (x_4, 2) - pow (x_3, 2))
                                        - x_3 * pow (x_4, 2)
                                        + pow (x_3, 2) * x_4
                                        + pow (x_2, 2) * (x_3 - x_4))
                      + pow (x_2, 3) * (x_3 * pow (x_4, 2) - pow (x_3, 2) * x_4));
        return a;
    }

    double get_b (QPointF p1, QPointF p2, QPointF p3, QPointF p4)
    {
        double x_1 = p1.x();
        double y_1 = p1.y();
        double x_2 = p2.x();
        double y_2 = p2.y();
        double x_3 = p3.x();
        double y_3 = p3.y();
        double x_4 = p4.x();
        double y_4 = p4.y();

        double b = - (x_1 * (pow (x_2, 3) * (y_4 - y_3) - pow (x_3, 3) * y_4 + pow (x_4,
                             3) * y_3
                             + (pow (x_3, 3) - pow (x_4, 3)) * y_2)
                      + x_2 * (pow (x_3, 3) * y_4 - pow (x_4, 3) * y_3)
                      + pow (x_1, 3) * (x_3 * y_4 + x_2 * (y_3 - y_4)
                                        - x_4 * y_3 + (x_4 - x_3) * y_2)
                      + pow (x_2, 3) * (x_4 * y_3 - x_3 * y_4) + (x_3 * pow (x_4, 3)
                              - pow (x_3, 3) * x_4) * y_2
                      + (x_2 * (pow (x_4, 3) - pow (x_3, 3)) - x_3 * pow (x_4, 3)
                         + pow (x_3, 3) * x_4 + pow (x_2, 3) * (x_3 - x_4)) * y_1)
                   / (x_1 * (pow (x_2, 2) * (pow (x_4, 3) - pow (x_3, 3))
                             - pow (x_3, 2) * pow (x_4, 3)
                             + pow (x_3, 3) * pow (x_4, 2)
                             + pow (x_2, 3) * (pow (x_3, 2) - pow (x_4, 2)))
                      + x_2 * (pow (x_3, 2) * pow (x_4, 3)
                               - pow (x_3, 3) * pow (x_4, 2))
                      + pow (x_1, 2) * (x_3 * pow (x_4, 3) + x_2 * (pow (x_3, 3)
                                        - pow (x_4, 3))
                                        + pow (x_2, 3) * (x_4 - x_3)
                                        - pow (x_3, 3) * x_4)
                      + pow (x_2, 2) * (pow (x_3, 3) * x_4 - x_3 * pow (x_4, 3))
                      + pow (x_1, 3) * (x_2 * (pow (x_4, 2) - pow (x_3, 2))
                                        - x_3 * pow (x_4, 2)
                                        + pow (x_3, 2) * x_4
                                        + pow (x_2, 2) * (x_3 - x_4))
                      + pow (x_2, 3) * (x_3 * pow (x_4, 2) - pow (x_3, 2) * x_4));
        return b;
    }

    double get_c (QPointF p1, QPointF p2, QPointF p3, QPointF p4)
    {
        double x_1 = p1.x();
        double y_1 = p1.y();
        double x_2 = p2.x();
        double y_2 = p2.y();
        double x_3 = p3.x();
        double y_3 = p3.y();
        double x_4 = p4.x();
        double y_4 = p4.y();

        double c = (pow (x_1, 2) * (pow (x_2, 3) * (y_4 - y_3) - pow (x_3, 3) * y_4
                                    + pow (x_4, 3) * y_3 + (pow (x_3, 3)
                                            - pow (x_4, 3)) * y_2)
                    + pow (x_2, 2) * (pow (x_3, 3) * y_4 - pow (x_4, 3) * y_3)
                    + pow (x_1, 3) * (pow (x_3, 2) * y_4
                                      + pow (x_2, 2) * (y_3 - y_4)
                                      - pow (x_4, 2) * y_3
                                      + (pow (x_4, 2) - pow (x_3, 2)) * y_2)
                    + pow (x_2, 3) * (pow (x_4, 2) * y_3 - pow (x_3, 2) * y_4)
                    + (pow (x_3, 2) * pow (x_4, 3)
                       - pow (x_3, 3) * pow (x_4, 2)) * y_2
                    + (pow (x_2, 2) * (pow (x_4, 3) - pow (x_3, 3))
                       - pow (x_3, 2) * pow (x_4, 3) + pow (x_3, 3) * pow (x_4, 2)
                       + pow (x_2, 3) * (pow (x_3, 2) - pow (x_4, 2))) * y_1)
                   / (x_1 * (pow (x_2, 2) * (pow (x_4, 3) - pow (x_3, 3))
                             - pow (x_3, 2) * pow (x_4, 3)
                             + pow (x_3, 3) * pow (x_4, 2)
                             + pow (x_2, 3) * (pow (x_3, 2) - pow (x_4, 2)))
                      + x_2 * (pow (x_3, 2) * pow (x_4, 3)
                               - pow (x_3, 3) * pow (x_4, 2))
                      + pow (x_1, 2) * (x_3 * pow (x_4, 3) +
                                        x_2 * (pow (x_3, 3) - pow (x_4, 3))
                                        + pow (x_2, 3) * (x_4 - x_3)
                                        - pow (x_3, 3) * x_4)
                      + pow (x_2, 2) * (pow (x_3, 3) * x_4 - x_3 * pow (x_4, 3))
                      + pow (x_1, 3) * (x_2 * (pow (x_4, 2) - pow (x_3, 2))
                                        - x_3 * pow (x_4, 2)
                                        + pow (x_3, 2) * x_4
                                        + pow (x_2, 2) * (x_3 - x_4))
                      + pow (x_2, 3) * (x_3 * pow (x_4, 2)
                                        - pow (x_3, 2) * x_4));

        return c;

    }

    double get_d (QPointF p1, QPointF p2, QPointF p3, QPointF p4)
    {
        double x_1 = p1.x();
        double y_1 = p1.y();
        double x_2 = p2.x();
        double y_2 = p2.y();
        double x_3 = p3.x();
        double y_3 = p3.y();
        double x_4 = p4.x();
        double y_4 = p4.y();

        double d = - (x_1 * (pow (x_2, 2) * (pow (x_3, 3) * y_4
                                             - pow (x_4, 3) * y_3)
                             + pow (x_2, 3) * (pow (x_4, 2) * y_3
                                               - pow (x_3, 2) * y_4)
                             + (pow (x_3, 2) * pow (x_4, 3)
                                - pow (x_3, 3) * pow (x_4, 2)) * y_2)
                      + pow (x_1, 2) * (x_2 * (pow (x_4, 3) * y_3
                                               - pow (x_3, 3) * y_4)
                                        + pow (x_2, 3) * (x_3 * y_4
                                                - x_4 * y_3)
                                        + (pow (x_3, 3) * x_4
                                           - x_3 * pow (x_4, 3)) * y_2)
                      + pow (x_1, 3) * (x_2 * (pow (x_3, 2) * y_4
                                               - pow (x_4, 2) * y_3)
                                        + pow (x_2, 2) * (x_4 * y_3 - x_3 * y_4)
                                        + (x_3 * pow (x_4, 2)
                                           - pow (x_3, 2) * x_4) * y_2)
                      + (x_2 * (pow (x_3, 3) * pow (x_4, 2)
                                - pow (x_3, 2) * pow (x_4, 3))
                         + pow (x_2, 2) * (x_3 * pow (x_4, 3)
                                           - pow (x_3, 3) * x_4)
                         + pow (x_2, 3) * (pow (x_3, 2) * x_4
                                           - x_3 * pow (x_4, 2))) * y_1)
                   / (x_1 * (pow (x_2, 2) * (pow (x_4, 3) - pow (x_3, 3))
                             - pow (x_3, 2) * pow (x_4, 3)
                             + pow (x_3, 3) * pow (x_4, 2)
                             + pow (x_2, 3) * (pow (x_3, 2)
                                               - pow (x_4, 2)))
                      + x_2 * (pow (x_3, 2) * pow (x_4, 3)
                               - pow (x_3, 3) * pow (x_4, 2))
                      + pow (x_1, 2) * (x_3 * pow (x_4, 3)
                                        + x_2 * (pow (x_3, 3) - pow (x_4, 3))
                                        + pow (x_2, 3) * (x_4 - x_3)
                                        - pow (x_3, 3) * x_4)
                      + pow (x_2, 2) * (pow (x_3, 3) * x_4 - x_3 * pow (x_4, 3))
                      + pow (x_1, 3) * (x_2 * (pow (x_4, 2) - pow (x_3, 2))
                                        - x_3 * pow (x_4, 2)
                                        + pow (x_3, 2) * x_4
                                        + pow (x_2, 2) * (x_3 - x_4))
                      + pow (x_2, 3) * (x_3 * pow (x_4, 2) - pow (x_3, 2) * x_4));
        return d;
    }

public:

    Interpolation_impl (QPointF p1, QPointF p2, QPointF p3, QPointF p4)
    {
        a = get_a (p1, p2, p3, p4);
        b = get_b (p1, p2, p3, p4);
        c = get_c (p1, p2, p3, p4);
        d = get_d (p1, p2, p3, p4);
    }
    double a, b, c, d;

    double y (double x)
    {
        double y = a * pow (x, 3) + b * pow (x, 2) + c * x + d;
        return y;
    }
};

CCubicFunctionSolver::CCubicFunctionSolver (QPointF p1, QPointF p2, QPointF p3,
        QPointF p4) :
    d (new Interpolation_impl (p1, p2, p3, p4))
{ }

CCubicFunctionSolver::~CCubicFunctionSolver()
{
    delete d;
}

double CCubicFunctionSolver::y (double x)
{
    return d->y (x);
}

QString CCubicFunctionSolver::deb_print()
{
    QString res = QString ("y(x) = %1 * x^3 + %2 x^2 + %3 x + %4")
                  .arg (d->a)
                  .arg (d->b)
                  .arg (d->c)
                  .arg (d->d);
    return res;
}
