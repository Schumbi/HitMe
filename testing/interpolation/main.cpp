#include "cinterpolation.h"
#include <iostream>
#include <cmath>

#include<QPointF>

int main (int argc, char** argv)
{
    Q_UNUSED (argc);
    Q_UNUSED (argv);

    double x1 = -4;
    double x2 = -2;
    double x3 = 1;
    double x4 = 80;


    QPointF p1 (x1, pow (x1 + 2, 3) + 2);
    QPointF p2 (x2, pow (x2 + 2, 3) + 2);

    QPointF p3 (x3, pow (x3 + 2, 3) + 2);
    QPointF p4 (x4, pow (x4 + 2, 3) + 2);

    CInterpolation i (p1, p2, p3, p4);

    std::cout << i.deb_print().toStdString() << std::endl;
    std::cout << "P(" << "-2," << i.y (-2) << ")" << std::endl;
    std::cout << "P(" << " 0," << i.y (0) << ")" << std::endl;
    std::cout << "P(" << " 4," << i.y (4) << ")" << std::endl;


    return 0;
}

