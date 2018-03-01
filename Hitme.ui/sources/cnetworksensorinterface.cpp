#include "cnetworksensorinterface.h"

#include <QNetworkDatagram>

CNetworkSensorInterface::CNetworkSensorInterface (const QHostAddress &sensorIP,
        QObject *parent) : QObject (parent), m_sensorAdress (sensorIP)
{
    m_udpCtrl.bind (QHostAddress::AnyIPv4, ctrl_port);
    m_udpData.bind (QHostAddress::AnyIPv4, data_port);

    connect (&m_udpCtrl, &QUdpSocket::readyRead, this,
             &CNetworkSensorInterface::readCtrlFromSensor);

    connect (&m_udpData, &QUdpSocket::readyRead, this,
             &CNetworkSensorInterface::readDataFromSensor);

}

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

void CNetworkSensorInterface::sendCommandToSensor (const QByteArray &data)
{
    m_udpCtrl.writeDatagram (data, data.size(),
                             m_sensorAdress,
                             ctrl_port);
}
