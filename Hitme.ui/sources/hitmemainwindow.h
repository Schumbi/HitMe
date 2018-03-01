#ifndef HITMEMAINWINDOW_H
#define HITMEMAINWINDOW_H

#include <QMainWindow>

#include "csensorstatus.h"

namespace Ui {
class HitmeMainWindow;
}

class CNetworkSensorInterface;
class CSensorCtrlProcessor;

class HitmeMainWindow : public QMainWindow {

    Q_OBJECT

private:
    bool accEnabled;
    CNetworkSensorInterface *m_sensor1;
    CSensorCtrlProcessor *m_ctrlProcessor;

public:
    explicit HitmeMainWindow (QWidget *parent = 0);
    ~HitmeMainWindow();

public slots:
    void getStatusMessage (const CSensorStatus& status);

private slots:
    void activateMeasuring (bool);


private:
    Ui::HitmeMainWindow *ui;
};

#endif // HITMEMAINWINDOW_H
