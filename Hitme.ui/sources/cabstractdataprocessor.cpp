#include "cabstractdataprocessor.h"

CAbstractDataProcessor::CAbstractDataProcessor (QObject *parent) : QObject (
        parent)
{}

CSensorStatus CAbstractDataProcessor::sensorStatus()
{
    return m_sensorstatus;
}

void CAbstractDataProcessor::processDatagram (const QNetworkDatagram &data)
{

    m_sensorstatus.set_fromIp (data.senderAddress().toString());
    m_sensorstatus.set_message ("");
    m_sensorstatus.set_state (CSensorStatus::ERR);

    processData (data.data(), m_sensorstatus);

    emit processingFinished();
}
