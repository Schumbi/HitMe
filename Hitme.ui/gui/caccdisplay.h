#ifndef CACCDISPLAY_H
#define CACCDISPLAY_H

#include <QWidget>
#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>

#include "../caccstorage.h"

class CAccDisplay : public QWidget {

    Q_OBJECT

    typedef QtCharts::QLineSeries series_t;

private:

    const int c_datacnt = 10000;

    QtCharts::QChart *m_chart;
    series_t *m_seriesX;
    series_t *m_seriesY;
    series_t *m_seriesZ;
    QtCharts::QChartView *m_chartView;

public:
    explicit CAccDisplay (QWidget *parent = 0);
    ~CAccDisplay();

public slots:
    void setData (const data_t &data);

};

#endif // CACCDISPLAY_H
