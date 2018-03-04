#include "cabstractdataprocessor.h"

CAbstractNetworkProcessor::CAbstractNetworkProcessor (QObject *parent) :
    QObject (
        parent)
{}

CSensorStatus CAbstractNetworkProcessor::sensorStatus()
{
    return m_sensorstatus;
}

void CAbstractNetworkProcessor::processDatagram (const QNetworkDatagram &data)
{

    m_sensorstatus.set_fromIp (data.senderAddress().toString());
    m_sensorstatus.set_message ("");
    m_sensorstatus.set_state (CSensorStatus::ERR);

    processData (data.data(), m_sensorstatus);

    emit processingFinished();
}
