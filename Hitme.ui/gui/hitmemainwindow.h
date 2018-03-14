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

protected slots:
    void deleteMessages();
    void statusUpdate();

private slots:
    void on_pushButton_startstop_clicked();

    void on_comboBox_sensitivity_currentIndexChanged (int index);

    void on_comboBox_bandwidth_currentIndexChanged (int index);

private:
    Ui::HitmeMainWindow *ui;
};

#endif // HITMEMAINWINDOW_H
