#include "csensordataprocessor.h"
#include "caccdataconverter.h"

CSensorDataProcessor::CSensorDataProcessor (QObject *parent)
    : CAbstractDataProcessor (parent)
{

}

bool CSensorDataProcessor::processData (const QByteArray &data,
                                        CSensorStatus &toFill)
{
    union
    {
        quint32 val32x1;
        quint16 val16x2[2];
        quint8 val8x4[4];
    } timeConv;

    CSensorData accData;
    // data[0] LSB
    // data[1]
    // data[2]
    // data[3] MSB time stamp
    timeConv.val8x4[0] = data[0];
    timeConv.val8x4[1] = data[1];
    timeConv.val8x4[2] = data[2];
    timeConv.val8x4[3] = data[3];
    accData.setTimestamp (timeConv.val32x1);

    conv16_t conv16;

    for (int ctr = 4; ctr < (data.size() - 6); ctr += 6)
    {
        conv16.data8x2[0] = data[ctr + 0];
        conv16.data8x2[1] = data[ctr + 1];
        uint16_t rawx = conv16.data16x1;
        conv16.data8x2[0] = data[ctr + 2];
        conv16.data8x2[1] = data[ctr + 3];
        uint16_t rawy = conv16.data16x1;
        conv16.data8x2[0] = data[ctr + 4];
        conv16.data8x2[1] = data[ctr + 5];
        uint16_t rawz = conv16.data16x1;
        auto accValues = CAccDataConverter (rawx, rawy, rawz);
        accData.append (QVector3D (accValues.x(), accValues.y(), accValues.z()));
    }

    toFill.set_message (QString());
    toFill.set_state (CSensorStatus::OK);

    emit processedData (accData);

    return true;
}
