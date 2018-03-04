#ifndef CABSTRACTCALCULATOR_H
#define CABSTRACTCALCULATOR_H

#include <QObject>
#include <csensordata.h>

class CAbstractCalculator : public QObject {

    Q_OBJECT

public:
    explicit CAbstractCalculator (QObject *parent = nullptr);

    virtual CSensorData calculate (const CSensorData &raw) = 0;

signals:
    void finished (CSensorData results);

public slots:

    virtual void calculateData (const CSensorData &raw);

};

#endif // CABSTRACTCALCULATOR_H
