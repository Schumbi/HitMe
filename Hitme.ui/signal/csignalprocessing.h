#ifndef CSIGNALPROCESSING_H
#define CSIGNALPROCESSING_H

#include <QObject>

#include <caccstorage.h>

#include <liquid/liquid.h>

namespace signal {

class CSignalProcessing : public QObject {
    Q_OBJECT

public:
    explicit CSignalProcessing (QObject *parent = nullptr);

    bool process (data_t &data, double &fac);

signals:

public slots:
};

}
#endif // CSIGNALPROCESSING_H
