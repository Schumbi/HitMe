#include "csensorctrlprocessor.h"

#include "csensorstatus.h"

#include <QRegularExpression>

CSensorCtrlProcessor::CSensorCtrlProcessor (QObject *parent)
    : CAbstractDataProcessor (parent)
{}

bool CSensorCtrlProcessor::processData (const QByteArray &data,
                                        CSensorStatus &toFill)
{
    QString dataS (data);
    QRegularExpression reg ("^(\\{F0:\\d\\})(.*)");

    QRegularExpressionMatch match = reg.match (dataS);

    if (match.hasMatch())
    {
        QString suc = match.captured (1);
        QString msg = match.captured (2);

        if (!suc.isNull())
        {
            CSensorStatus::e_sensorstate state = CSensorStatus::ERR;
            suc.remove ("{F0:");
            suc.remove ('}');

            bool ok = false;
            int i = suc.toInt (&ok);

            if (ok)
            {
                state = static_cast<CSensorStatus::e_sensorstate>
                        (i);
            }

            toFill.set_state (state);
            qDebug() << toFill;
        }

        if (msg.isNull() == false)
        {
            toFill.set_message (msg);
        }

        return true;
    }

    return false;
}

void CSensorCtrlProcessor::processDatagram (const QNetworkDatagram &netData)
{
    CSensorStatus status;
    status.set_fromIp (netData. senderAddress().toString());

    processData (netData.data(), status);

    emit processedStatus (status);

}
