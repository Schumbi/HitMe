#ifndef CSENSOR_H
#define CSENSOR_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class CNetworkSensorInterface : public QObject {

    Q_OBJECT

private:
    QHostAddress m_sensorAdress;
    QUdpSocket m_udpCtrl;
    QUdpSocket m_udpData;

public:
    explicit CNetworkSensorInterface (const QHostAddress &sensorIP,
                                      QObject *parent = nullptr);

    static constexpr quint32 ctrl_port = 10001;
    static constexpr quint32 data_port = 10000;

private slots:
    void readCtrlFromSensor();
    void readDataFromSensor();


signals:
    void udp_Ctrl_received (const QNetworkDatagram &datagram);
    void udp_Data_received (const QNetworkDatagram &datagram);

public slots:
    void sendCommandToSensor (const QByteArray &m_udpData);

};

#endif // CSENSOR_H
