#ifndef HITMEMAINWINDOW_H
#define HITMEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class HitmeMainWindow;
}

class CSensor;

class HitmeMainWindow : public QMainWindow {

    Q_OBJECT

private:
    bool accEnabled;
    CSensor *sensor1;

public:
    explicit HitmeMainWindow (QWidget *parent = 0);
    ~HitmeMainWindow();

public slots:
    void getStatusMessage (const QByteArray &data);

private slots:
    void activateMeasuring (bool);


private:
    Ui::HitmeMainWindow *ui;
};

#endif // HITMEMAINWINDOW_H
