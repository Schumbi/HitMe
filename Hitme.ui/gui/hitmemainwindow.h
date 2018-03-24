#ifndef HITMEMAINWINDOW_H
#define HITMEMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <csensordata.h>
#include <csensor.h>
#include <csignalprocessing.h>

namespace Ui {
class HitmeMainWindow;
}

class CAccDisplay;

class HitmeMainWindow final : public QMainWindow {

    Q_OBJECT

private:
    QTimer caliTimer;
    bool calibrating;
    // timer that control update frequency of data in ui
    QTimer updateTimer;
    // state to show if measurement is enabled
    bool accEnabled;
    // a sensor
    sensor::CSensor* m_sensor1;
    // the calculator
    signal::CSignalProcessing* m_sigCalc;
    // a display widget
    CAccDisplay *m_accdisplay;
    // number of values to show in ui widgeht
    int valuesToShow;
    // bias of values (x,y,z)
    QVector3D m_dataBias;

public:
    explicit HitmeMainWindow (QWidget *parent = 0);
    ~HitmeMainWindow();

protected slots:
    void deleteMessages();
    // updates stats of sensor in ui from sensors data
    void statusUpdate();
    // updates acc data in ui (show data from sensor)
    void updateUI();
    // send processor calibration stop signal
    void stopCalibration();
    void startCalibration();
private slots:
    // start sensor
    void on_pushButton_startstop_clicked();
    // set sensitivity
    void on_comboBox_sensitivity_currentIndexChanged (int index);
    // set sensors internal filter bandwidth
    void on_comboBox_bandwidth_currentIndexChanged (int index);
    // enable/disable sensor input fields in ui
    void enableUIInput (bool enable);
    // calibrate data from sensor
    void calibratedData (QVector3D biases);

    void on_pushButton_calibration_clicked();

    void stopSensor();
    void startSensor();

    void on_spinBox_duration_valueChanged (int arg1);

private:
    Ui::HitmeMainWindow *ui;
};

#endif // HITMEMAINWINDOW_H
