#ifndef CACCDATACONVERTER_H
#define CACCDATACONVERTER_H

#include <cstdint>

union conv16_t
{
    uint16_t data16x1;
    uint8_t  data8x2[2];
};

class CAccDataConverter {

    int16_t m_x;
    int16_t m_y;
    int16_t m_z;

    int16_t twoCompToDec (uint16_t in, uint8_t highestBit);
    int16_t transfromToData (uint16_t raw);

public:
    CAccDataConverter() {}
    explicit CAccDataConverter (uint16_t rawx,
                                uint16_t rawy,
                                uint16_t rawz)
    {
        m_x = transfromToData (rawx);
        m_y = transfromToData (rawy);
        m_z = transfromToData (rawz);
    }

    int x() const
    {
        return m_x;
    }
    int y()  const
    {
        return m_y;
    }
    int z()  const
    {
        return m_z;
    }
};


#endif // CACCDATACONVERTER_H
