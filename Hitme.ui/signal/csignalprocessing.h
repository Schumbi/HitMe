#ifndef CSIGNALPROCESSING_H
#define CSIGNALPROCESSING_H

#include <QObject>

#include <caccstorage.h>

#include <liquid/liquid.h>

namespace signal {

class CSignalProcessing : public QObject {
    Q_OBJECT

    iirfilt_rrrf q;

public:
    explicit CSignalProcessing (QObject *parent = nullptr);
    virtual ~CSignalProcessing();

    bool process (data_t &data);



signals:

public slots:
};

}
#endif // CSIGNALPROCESSING_H
