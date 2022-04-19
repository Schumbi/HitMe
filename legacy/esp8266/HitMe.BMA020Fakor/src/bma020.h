#ifndef BMA020_H
#define BMA020_H

#include <Arduino.h>

#include "sensortypes.h"

static const uint8_t BMA029ADDR = 0x38;
extern const uint8_t BMA029ADDR;

using namespace sensor;

class Fake_BMA020 {
public:

    static const uint8_t accPacket = 2u + 2u + 2u;  // 2x + 2y + 2z = 6 byte

    Fake_BMA020();

    virtual void begin (uint8_t reg1, uint8_t reg2);
    virtual uint8_t writeReg (uint8_t reg, uint8_t value);
    virtual uint8_t readReg (uint8_t reg, uint8_t *buf, uint8_t &size);
    virtual void resetAcc();
    // bandwidth
    virtual bool setBandwidth (BMA020BANDWIDTH bandwidth);
    virtual BMA020BANDWIDTH getBandwidth ();
    virtual bool setRange (BMA020RANGE e_setup_acc);
    virtual BMA020RANGE getRange ();
    virtual bool isBMAReadable ();
    virtual bool tryFetchNewData (uint8_t* accBuf, uint16_t& curCount,
                                  uint16_t bufSize);
    virtual String getConfig();

private:
    uint8_t e_setup_acc;
    size_t fakeValCounter = 0;
    uint8_t getFakeVal();

};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_TWOWIRE)
    static Fake_BMA020 Fake_Bma020;
    extern Fake_BMA020 Fake_Bma020;
#endif

#endif // BMA020_H
