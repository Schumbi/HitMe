#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow (const AccDataReceiver& rec, QWidget *parent) :
    QMainWindow (parent),
    ui (new Ui::MainWindow)
{
    ui->setupUi (this);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->createDefaultAxes();


    m_seriesx = new QtCharts::QValueAxis (chart);

    m_seriesy = new QtCharts::QSplineSeries (chart);
    chart->setAxisY (m_seriesx, m_seriesy);
    chart->addSeries (m_seriesy);
    view = new QtCharts::QChartView (chart);
    ui->frame_data->layout()->addWidget (view);

    QObject::connect (&rec, &AccDataReceiver::dataReady,
                      this, &MainWindow::showData);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showData (const QVector<int> &data)
{
    for (int ctr = 0; ctr < data.size(); ctr++)
    {
        auto datum = data[ctr];
        m_seriesy->append (ctr, datum);
    }
}

