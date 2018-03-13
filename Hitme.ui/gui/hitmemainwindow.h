#ifndef HITMEMAINWINDOW_H
#define HITMEMAINWINDOW_H

#include <QMainWindow>

#include <csensordata.h>
#include "../csensor.h"

namespace Ui {
class HitmeMainWindow;
}

class CAccDisplay;

class HitmeMainWindow : public QMainWindow {

    Q_OBJECT

private:
    bool accEnabled;

    sensor::CSensor* m_sensor1;

    CAccDisplay *m_accdisplay;

public:
    explicit HitmeMainWindow (QWidget *parent = 0);
    ~HitmeMainWindow();


public slots:

private slots:
    void statusUpdate();

private:
    Ui::HitmeMainWindow *ui;
};

#endif // HITMEMAINWINDOW_H
