#ifndef CSIGNALPROCESSINGPRIVATE_H
#define CSIGNALPROCESSINGPRIVATE_H

#include <caccstorage.h>
#include <QObject>
#include <QList>

namespace signal
{

class CSignalProcessing;
class CAbstractProcessor;

class CSignalProcessingPrivate final : public QObject
{

    Q_OBJECT

    static constexpr int maxTempStorage = 5000;

    const CSignalProcessing *p;
    // biases
    QVector3D m_bias;
    // state of calibration
    bool m_isCalibrating;
    QVector3D m_maxValue;
    // required storage to calculate biases
    QVector<QVector3D> tempStorage;
    // calibration function
    void calibrate ( const data_t &data );
    double m_conversionFactor;
    QList<CAbstractProcessor *> procList;

public:
    explicit CSignalProcessingPrivate ( CSignalProcessing *p );
    virtual ~CSignalProcessingPrivate();
    // process any data
    void process ( data_t &data );
    // return calibration state
    bool isCalibrating() const;
    // return bias
    QVector3D bias() const;
    QVector3D maxValue() const;

    double conversionFactor() const;
    void setConversionFactor ( double conversionFactor );

public slots:
    // control calibration state
    void setCalibrating ( bool m_isCalibrating );

protected slots:
    void setMaxValue ( QVector3D val );
};

}
#endif // CSIGNALPROCESSINGPRIVATE_H
