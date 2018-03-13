#ifndef CACCDISPLAY_H
#define CACCDISPLAY_H

#include <QWidget>
#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include "../caccstorage.h"

class CAccDisplay : public QWidget {

    Q_OBJECT

private:

    const int c_datacnt = 10000;

    QtCharts::QChart *m_chart;
    QtCharts::QLineSeries *m_seriesX;
    QtCharts::QLineSeries *m_seriesY;
    QtCharts::QLineSeries *m_seriesZ;
    QtCharts::QChartView *m_chartView;

public:
    explicit CAccDisplay (QWidget *parent = 0);
    ~CAccDisplay();

public slots:
    void setData (const data_t &data);

};

#endif // CACCDISPLAY_H
