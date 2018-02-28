#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QObject>


#include "accdata.h"
#include "accDataReceiver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow (const AccDataReceiver &rec, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showData (const QVector<int> &data);

private:
    QtCharts::QValueAxis *m_seriesx;
    QtCharts::QSplineSeries *m_seriesy;

    void updateView();
    QtCharts::QChartView *view;
    Ui::MainWindow *ui;
    QVector<accData> _accData;
};

#endif // MAINWINDOW_H
