#include "caccdisplay.h"

#include <QDebug>

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
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
    m_seriesX = new QLineSeries;
    m_seriesY = new QLineSeries;
    m_seriesZ = new QLineSeries;
    m_chart->addSeries (m_seriesX);
    m_chart->addSeries (m_seriesY);
    m_chart->addSeries (m_seriesZ);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange (0, c_datacnt);
    axisX->setLabelFormat ("%g");
    axisX->setTitleText ("Time");

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange (-600, 600);
    axisY->setTitleText ("Acceleration");
    m_chart->setAxisX (axisX, m_seriesX);
    m_chart->setAxisY (axisY, m_seriesX);
    m_chart->legend()->hide();
    m_chart->setTitle (QString ("Data from Accaleration sensor"));


    m_seriesY->attachAxis (axisX);
    m_seriesY->attachAxis (axisY);
    m_seriesZ->attachAxis (axisX);
    m_seriesZ->attachAxis (axisY);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget (m_chartView);
    setLayout (mainLayout);

}

CAccDisplay::~CAccDisplay()
{}

void CAccDisplay::setData (const data_t &data)
{
    if (data.size() == 0)
    {
        return;
    }

    int start = data.size() < c_datacnt ? 0 : data.size() - c_datacnt;
    int size = data.size() < c_datacnt ? data.size() : c_datacnt;

    QVector<QPointF> pointsX;
    pointsX.reserve (size);
    QVector<QPointF> pointsY;
    pointsY.reserve (size);
    QVector<QPointF> pointsZ;
    pointsZ.reserve (size);

    for (int ctr = start; ctr < data.size(); ctr++)
    {
        pointsX.append (QPointF (data[ctr].w() / 1000000.0, data[ctr].x()));
        pointsY.append (QPointF (data[ctr].w() / 1000000.0, data[ctr].y()));
        pointsZ.append (QPointF (data[ctr].w() / 1000000.0, data[ctr].z()));
    }

    m_chart->axisX()->setRange (data[start].w() / 1000000.0,
                                data.last().w() / 1000000.0);

    m_seriesX->replace (pointsX);
    m_seriesY->replace (pointsY);
    m_seriesZ->replace (pointsZ);
}

