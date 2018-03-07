#ifndef HITMEMAINWINDOW_H
#define HITMEMAINWINDOW_H

#include <QMainWindow>

#include <csensorstatus.h>
#include <csensordata.h>
#include "../caccstorage.h"

namespace Ui {
class HitmeMainWindow;
}

class CNetworkSensorInterface;
class CSensorCtrlTransceiver;
class CSensorDataReceiver;
class CAccDisplay;

class HitmeMainWindow : public QMainWindow {

    Q_OBJECT

private:
    bool accEnabled;
    CNetworkSensorInterface *m_sensor1;
    CSensorCtrlTransceiver *m_ctrlProcessor;
    CSensorDataReceiver *m_dataProcessor;
    CAccStorage m_storage;
    CAccDisplay *m_accdisplay;

public:
    explicit HitmeMainWindow (QWidget *parent = 0);
    ~HitmeMainWindow();

public slots:
    void showStatusMessage (const CSensorStatus& status);

private slots:
    void activateMeasuring (bool);
    void showData (quint64 pkg);


private:
    Ui::HitmeMainWindow *ui;
};

#endif // HITMEMAINWINDOW_H
