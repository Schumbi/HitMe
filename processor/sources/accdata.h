#ifndef ACCDATA_H
#define ACCDATA_H

#include <cstdint>

union conv32_t
{
    uint32_t data32x1;
    uint16_t data16x2[2];
    uint8_t  data8x4[4];
};

union conv16_t
{
    uint16_t data16x1;
    uint8_t  data8x2[2];
};

class accDataConverter {

    int16_t _x;
    int16_t _y;
    int16_t _z;
    uint32_t _time;

    int16_t twoCompToDec (uint16_t in, uint8_t highestBit);
    int16_t transfromToData (uint16_t raw);

public:
    accDataConverter() {}
    explicit accDataConverter (uint16_t rawx, uint16_t rawy, uint16_t rawz,
                               uint32_t time)
    {
        _x = transfromToData (rawx);
        _y = transfromToData (rawy);
        _z = transfromToData (rawz);
        _time = time;
    }

    int x() const
    {
        return _x;
    }
    int y()  const
    {
        return _y;
    }
    int z()  const
    {
        return _z;
    }
};


#endif // ACCDATA_H
