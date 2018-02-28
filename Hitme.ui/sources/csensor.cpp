#include "csensor.h"

#include <QNetworkDatagram>

CSensor::CSensor (QObject *parent) : QObject (parent)
{
    ctrl = new QUdpSocket (this);
    ctrl->bind (QHostAddress::AnyIPv4, ctrl_port);

    connect (ctrl, &QUdpSocket::readyRead, this, &CSensor::readCtrlDatagram);

//    data = new QUdpSocket (this);
//    ctrl->bind (QHostAddress::AnyIPv4, data_port);

}

void CSensor::readCtrlDatagram()
{
    while (ctrl->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = ctrl->receiveDatagram();
        emit dataReceived (datagram.data());
    }
}

void CSensor::sendData (const QByteArray &data)
{
    ctrl->writeDatagram (data, data.size(), QHostAddress (QString ("192.168.1.5")),
                         ctrl_port);
}
