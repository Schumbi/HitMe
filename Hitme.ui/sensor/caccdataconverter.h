#ifndef CACCDATACONVERTER_H
#define CACCDATACONVERTER_H

#include <cstdint>

class CAccDataConverter {

    int16_t m_x;
    int16_t m_y;
    int16_t m_z;

    int16_t twoCompToDec (uint16_t in, uint8_t highestBit);
    int16_t transfromToData (uint16_t raw);

public:

    union conv32_t
    {
        uint32_t val32x1;
        uint16_t val16x2[2];
        uint8_t  val8x4[4];
    };

    union conv16_t
    {
        uint16_t data16x1;
        uint8_t  data8x2[2];
    };

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
