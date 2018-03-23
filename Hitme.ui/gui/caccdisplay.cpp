#include "caccdisplay.h"

#include <QDebug>

#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>

QT_CHARTS_USE_NAMESPACE

CAccDisplay::CAccDisplay (QWidget *parent) :
    QWidget (parent),
    m_chart (0),
    m_seriesX (0),
    m_chartView (0)
{
    m_chart = new QChart;
    m_chartView = new QChartView (m_chart);
    m_seriesX = new series_t;
//    m_seriesY = new series_t;
//    m_seriesZ = new series_t;
    m_chart->addSeries (m_seriesX);
//    m_chart->addSeries (m_seriesY);
//    m_chart->addSeries (m_seriesZ);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange (-1, 0);
    axisX->setLabelFormat ("%d");
    axisX->setTitleText ("Time");

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange (-5, 600);
    axisY->setTitleText ("Acceleration");
    m_chart->setAxisX (axisX, m_seriesX);
    m_chart->setAxisY (axisY, m_seriesX);
    m_chart->legend()->hide();
    m_chart->setTitle (QString ("Data from Accaleration sensor"));


//    m_seriesY->attachAxis (axisX);
//    m_seriesY->attachAxis (axisY);
//    m_seriesZ->attachAxis (axisX);
//    m_seriesZ->attachAxis (axisY);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget (m_chartView);
    setLayout (mainLayout);

}

CAccDisplay::~CAccDisplay()
{}

void CAccDisplay::setData (const data_t &data,
                           double ymin, double ymax,
                           const double timeStretch)
{
    if (data.size() == 0)
    {
        return;
    }

    int size = data.size();

    QVector<QPointF> pointsX;
    pointsX.reserve (size);

    double end = data.last().w();
    double beg = data.first().w();

    for (int ctr = 0; ctr < data.size(); ctr++)
    {
        pointsX.append (QPointF ((data[ctr].w() - end) / timeStretch,
                                 data[ctr].x()));
    }

    m_chart->axisX()->setRange ((beg - end) / timeStretch, 0);
    m_chart->axisY()->setRange (ymin, ymax);

    m_seriesX->replace (pointsX);
}

