#include "server.h"

#include <QNetworkDatagram>
#include <QHostInfo>
#include <QList>
#include <QtDebug>


uint32_t oldTime = 0;
void Server::processData (const QByteArray& data)
{
    conv32_t conv32;
    conv16_t conv16;
    // get time stamp
    int ctr = 0;

    for (; ctr < 4; ctr++)
    {
        conv32.data8x4[ctr] = data.constData()[ctr];
    }

    uint32_t time = conv32.data32x1;
    uint32_t diff = time - oldTime;
    double bw = (184 / (diff / 1000.0 / 1000.0) / 1024);

    // get rest of data
    for (ctr = 4; ctr < (data.size() - 6); ctr += 6)
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

        auto d = accDataConverter (rawx, rawy, rawz, time);
        qDebug() << "diff PC: " << timeElapsed  << " diff MC: " <<
                 QString::number (diff / 1000.0, 'f', 0) <<  "bw:" <<
                 QString::number (
                     bw, 'f', 0) <<
                 "mus bytes: " <<
                 data.size() << " x: " << d.x() <<
                 " y: " << d.y() << " z: "
                 << d.z();
        dataVec.append (d);

    }

    oldTime = time;
}

Server::Server (QObject *parent) : QThread (parent)
{
    udpSocket = new QUdpSocket (this);
    udpSocket->bind (10000);

    tim = new QElapsedTimer();
    tim->start();

    QObject::connect (udpSocket, SIGNAL (readyRead()), this,
                      SLOT (readingPendingDatagrams()));
}



void Server::readingPendingDatagrams()
{
    QByteArray datagram;
    timeElapsed = tim->elapsed();

    // using QUdpSocket::readDatagram (API since Qt 4)
    while (udpSocket->hasPendingDatagrams())
    {
        datagram.resize (int (udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram (datagram.data(), datagram.size());
        processData (datagram.constData());
        qDebug() << (tr ("size: \"%1\" (Vec: %2)")
                     .arg (datagram.size()).arg (dataVec.size()));
    }

    tim->restart();

}
