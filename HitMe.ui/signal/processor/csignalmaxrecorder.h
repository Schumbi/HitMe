#ifndef CSIGNALMAXRECORDER_H
#define CSIGNALMAXRECORDER_H

#include "../cabstractprocessor.h"

namespace signal {


class CSignalMaxRecorder : public CAbstractProcessor {

    Q_OBJECT

    int m_maxCtr = 3;    // required num of values to store data to file
    const int m_pkgSize = 30;  // num of acc val per packet from sensor
    const int m_threshold = 510; // threshold that qAbs(accVal) must exceed

public:
    explicit CSignalMaxRecorder ( CSignalProcessing *p );

    // CAbstractProcessor interface
    int maxCtr() const;
    void setMaxCtr (int maxCtr);

protected:
    virtual void changeData (data_t &data);
};

}

#endif // CSIGNALMAXRECORDER_H
