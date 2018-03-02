#include "cnetworksensorinterface.h"

#include <QNetworkDatagram>

CNetworkSensorInterface::CNetworkSensorInterface (const QHostAddress &sensorIP,
        QObject *parent,
        quint32 ctrl_port,
        quint32 data_port)
    : QObject (parent),
      m_sensorAdress (sensorIP),
      m_ctrl_port (ctrl_port),
      m_data_port (data_port)
{
    // bind to any local adress and local port
    m_udpCtrl.bind (QHostAddress::AnyIPv4, m_ctrl_port);
    m_udpData.bind (QHostAddress::AnyIPv4, m_data_port);

    // process ctrl data on arival
    connect (&m_udpCtrl, &QUdpSocket::readyRead, this,
             &CNetworkSensorInterface::readCtrlFromSensor);

    // process acc data on arival
    connect (&m_udpData, &QUdpSocket::readyRead, this,
             &CNetworkSensorInterface::readDataFromSensor);

}

// process ctrl data on arival
void CNetworkSensorInterface::readCtrlFromSensor()
{
    while (m_udpCtrl.hasPendingDatagrams())
    {
        QNetworkDatagram datagram = m_udpCtrl.receiveDatagram();

        if (datagram.senderAddress() == m_sensorAdress)
        {
            emit udp_Ctrl_received (datagram);
        }
    }
}

// process acc data on arival
void CNetworkSensorInterface::readDataFromSensor()
{
    while (m_udpData.hasPendingDatagrams())
    {
        QNetworkDatagram datagram = m_udpData.receiveDatagram();

        if (datagram.senderAddress() == m_sensorAdress)
        {
            emit udp_Data_received (datagram);
        }
    }
}

// send a byte array to the sensor (should follow sensor format)
void CNetworkSensorInterface::sendCommandToSensor (const QByteArray &data)
{
    m_udpCtrl.writeDatagram (data, data.size(),
                             m_sensorAdress,
                             m_ctrl_port);
}
