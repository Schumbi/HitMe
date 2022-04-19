#include "hitmemainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HitmeMainWindow w;
    w.show();

    return a.exec();
}
