#ifndef CSIGNALPROCESSING_H
#define CSIGNALPROCESSING_H

#include <QObject>

#include <caccstorage.h>

#include <liquid/liquid.h>

namespace signal {

class CSignalProcessingPrivate;

class CSignalProcessing : public QObject {

    Q_OBJECT

    CSignalProcessingPrivate *d;

public:
    explicit CSignalProcessing (QObject *parent = nullptr);
    virtual ~CSignalProcessing();

    void process (data_t &data);

    double conversionFactor() const;
    void setConversionFactor (double conversionFactor);

    QVector3D bias();
    QVector3D maxValue();

signals:
    void calibrated (QVector3D bias) const;

public slots:
    void setCalibrating (bool state);
};

}
#endif // CSIGNALPROCESSING_H
