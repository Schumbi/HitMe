#include "bma020.h"
#include "fakedata.h"
#include "sensor.h"

#include <Arduino.h>


Fake_BMA020::Fake_BMA020()
{
}

void Fake_BMA020::begin (uint8_t reg1, uint8_t reg2)
{
    // useless
    reg1 += reg2;
}

uint8_t Fake_BMA020::writeReg (uint8_t reg, uint8_t value)
{
    switch (reg)
    {
    case E_SETUP_ACC:
        e_setup_acc = value;
        break;
    }

    return true;
}

uint8_t Fake_BMA020::readReg (uint8_t reg, uint8_t *buf, uint8_t &size)
{
    size = 1;

    switch (reg)
    {
    case E_CHIPID:
        (*buf) = 2;
        delayMicroseconds (500);
        break;

    case E_SETUP_ACC:
        (*buf) = e_setup_acc;
        delayMicroseconds (500);
        break;

    // get some fake values
    case BMA020REGISTER::E_DATA_LSBX:
        const uint8_t maxReadSize = accPacket;
        size = maxReadSize;
        size_t ctr = 0;

        for (ctr = 0; ctr < maxReadSize; ctr++)
        {
            buf[ctr] = getFakeVal();
            delayMicroseconds (1000 / 6);
        }

        break;
    }

    return size;
}

void Fake_BMA020::resetAcc()
{
    delay (101);
}

// R14h bandwidth
constexpr uint8_t _BW0 = 0x0u;
constexpr uint8_t _BW1 = 0x1u;
constexpr uint8_t _BW2 = 0x2u;
constexpr uint8_t _DONTUSE0 = 0x5u;
constexpr uint8_t _DONTUSE1 = 0x6u;
constexpr uint8_t _DONTUSE2 = 0x7u;
constexpr uint8_t _bit_mask_Bandwidth = (1 << _BW0) | (1 << _BW1) | (1 << _BW2);
constexpr uint8_t att_mask = (uint8_t) ((1 << _DONTUSE0) | (1 << _DONTUSE1) |
                                        (1 << _DONTUSE2));

bool Fake_BMA020::setBandwidth (BMA020BANDWIDTH bandwidth)
{
    uint8_t buf;
    uint8_t size = 1;

    if (!readReg (E_SETUP_ACC, &buf, size))
    {
        return false;
    }

    auto reg_14h = buf;
    // preserve highest bits
    uint8_t attention = reg_14h & att_mask;
    // 11100111b = 11111111b ^ 00011000b
    auto delMask =  ~_bit_mask_Bandwidth;
    // clear wanted bits
    reg_14h &= delMask;
    // and reset them with new value
    reg_14h |= ((uint8_t)bandwidth << _BW0);
    // restore highest bits
    delMask = ~att_mask;
    reg_14h &= delMask;
    reg_14h |= attention;
    writeReg (E_SETUP_ACC, reg_14h);
    delay (50);
    auto bw = getBandwidth ();
    return bw == bandwidth;
}

BMA020BANDWIDTH Fake_BMA020::getBandwidth ()
{
    uint8_t buf;
    uint8_t size = 1;
    readReg (E_SETUP_ACC, &buf, size);
    return (BMA020BANDWIDTH) ((buf & _bit_mask_Bandwidth) >> _BW0);
}

// R14h ranges
constexpr uint8_t _RANGE0 = 0x3u;
constexpr uint8_t _RANGE1 = 0x4u;
constexpr uint8_t _bit_mask_Range = (1 << _RANGE0) | (1 << _RANGE1);

bool Fake_BMA020::setRange (BMA020RANGE range)
{
    uint8_t reg_14h;
    uint8_t size = 1;

    if (!readReg (E_SETUP_ACC, &reg_14h, size))
    {
        return false;
    }

    // preserve highest bits
    uint8_t attention = reg_14h & att_mask;
    // 11100111b = 11111111b ^ 00011000b
    auto delMask = ~_bit_mask_Range;
    // clear wanted bits
    reg_14h &= delMask;
    // and reset them with new value
    reg_14h |= range << _RANGE0;
    // restore highest bits
    delMask = ~att_mask;
    reg_14h &= delMask;
    reg_14h |= attention;
    writeReg (E_SETUP_ACC, reg_14h);
    auto rg = getRange ();
    return rg == range;
}

BMA020RANGE Fake_BMA020::getRange ()
{
    uint8_t reg_14h;
    uint8_t size = 1;
    readReg (E_SETUP_ACC, &reg_14h, size);
    return static_cast<BMA020RANGE> ((reg_14h & _bit_mask_Range) >> _RANGE0);
}

bool Fake_BMA020::isBMAReadable ()
{
    uint8_t id = 0;
    uint8_t size = 1;
    readReg (E_CHIPID, &id, size);
    return  id == 2;
}

bool Fake_BMA020::tryFetchNewData (uint8_t *accBuf,
                                   uint16_t &curCount,
                                   uint16_t bufSize)
{
    bool dataAvail = false;

    const uint8_t maxReadSize = accPacket;
    uint8_t buf[maxReadSize];
    uint8_t size = maxReadSize;
    readReg (BMA020REGISTER::E_DATA_LSBX, buf, size);

    if (size == maxReadSize)
    {
        dataAvail = ((buf[0] & 1) + (buf[2] & 1) + (buf[4] & 1)) == 3;

        if (dataAvail)
        {
            memcpy (accBuf + curCount, buf, size);
            curCount += size;
        }
    }

    // return true, if buff is full
    // (no more maxReadSize will fit)
    return curCount > (bufSize - size);
}

String Fake_BMA020::getConfig()
{
    if (isBMAReadable() == false)
    {
        return String();
    }

    String config = "{\"Range\":\"" + String (getRange()) +
                    "\",\"Bandwidth\":\"" + getBandwidth() + "\"}";
    return  config;
}

uint8_t Fake_BMA020::getFakeVal()
{
    uint8_t ret = data[fakeValCounter];

    // add one to ctr
    fakeValCounter += 1;

    // and reset if full
    if (fakeValCounter >= sizeData)
    {
        fakeValCounter = 0;
    }

    return ret;
}
