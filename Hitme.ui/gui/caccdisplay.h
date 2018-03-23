#ifndef CACCDISPLAY_H
#define CACCDISPLAY_H

#include <QWidget>
#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>

#include <caccstorage.h>

class CAccDisplay : public QWidget {

    Q_OBJECT

    typedef QtCharts::QLineSeries series_t;

private:

    QtCharts::QChart *m_chart;
    series_t *m_seriesX;
    QtCharts::QChartView *m_chartView;

public:
    explicit CAccDisplay (QWidget *parent = 0);
    ~CAccDisplay();

public slots:
    void setData (const data_t &data, double ymin, double ymax,
                  const double timeStretch = 1000000);

};

#endif // CACCDISPLAY_H
