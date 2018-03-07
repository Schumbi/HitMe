#include "csensorctrltransceiver.h"

#include "csensorstatus.h"

#include <QRegularExpression>

CSensorCtrlTransceiver::CSensorCtrlTransceiver (QObject *parent)
    : CAbstractNetworkProcessor (parent)
{}

bool CSensorCtrlTransceiver::processData (const QByteArray &data,
        CSensorStatus &toFill)
{
    bool retVal = false;
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
        }

        if (msg.isNull() == false)
        {
            toFill.set_message (msg);
        }

        retVal = true;
    }

    qDebug() << toFill;
    emit processedStatus (toFill);

    return retVal;
}
