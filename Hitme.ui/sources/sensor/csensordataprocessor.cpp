#include "csensordataprocessor.h"
#include "caccdataconverter.h"

CSensorDataProcessor::CSensorDataProcessor (QObject *parent)
    : CAbstractNetworkProcessor (parent)
{

}

bool CSensorDataProcessor::processData (const QByteArray &data,
                                        CSensorStatus &toFill)
{
    CAccDataConverter::conv32_t conv32;
    CAccDataConverter::conv16_t conv16;

    CSensorData accData;
    // data[0] LSB
    // data[1]
    // data[2]
    // data[3] MSB time stamp begin
    conv32.val8x4[0] = data[0];
    conv32.val8x4[1] = data[1];
    conv32.val8x4[2] = data[2];
    conv32.val8x4[3] = data[3];
    accData.setStartTimestamp (conv32.val32x1);
    // data[0] LSB
    // data[1]
    // data[2]
    // data[3] MSB time stamp end
    conv32.val8x4[0] = data[4];
    conv32.val8x4[1] = data[5];
    conv32.val8x4[2] = data[6];
    conv32.val8x4[3] = data[7];
    accData.setEndTimestamp (conv32.val32x1);
    // data[4] LSB
    // data[5]
    // data[6]
    // data[7] MSB packet id (sensor)
    conv32.val8x4[0] = data[8];
    conv32.val8x4[1] = data[9];
    conv32.val8x4[2] = data[10];
    conv32.val8x4[3] = data[11];
    accData.setId (conv32.val32x1);

    // extract data
    for (int ctr = 8; ctr < (data.size() - 6); ctr += 6)
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

    toFill.set_message (QString ("{\"ret\":\"ACC data converted\"}"));
    toFill.set_state (CSensorStatus::OK);
    qDebug() << accData;

    emit processedData (accData);

    return true;
}
