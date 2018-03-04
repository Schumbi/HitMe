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
class CSensorCtrlProcessor;
class CSensorDataProcessor;

class HitmeMainWindow : public QMainWindow {

    Q_OBJECT

private:
    bool accEnabled;
    CNetworkSensorInterface *m_sensor1;
    CSensorCtrlProcessor *m_ctrlProcessor;
    CSensorDataProcessor *m_dataProcessor;
    CAccStorage m_storage;

public:
    explicit HitmeMainWindow (QWidget *parent = 0);
    ~HitmeMainWindow();

public slots:
    void showStatusMessage (const CSensorStatus& status);
    void showAccData (const CSensorData& data);

private slots:
    void activateMeasuring (bool);


private:
    Ui::HitmeMainWindow *ui;
};

#endif // HITMEMAINWINDOW_H
