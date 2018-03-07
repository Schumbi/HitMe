#ifndef CSENSOR_H
#define CSENSOR_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

/*!
 * \brief The CNetworkSensorInterface class
 */

class CNetworkSensorInterface : public QObject {

    Q_OBJECT

private:
    // network config
    QHostAddress m_sensorAdress;
    quint32 m_ctrl_port;
    quint32 m_data_port;

    QUdpSocket m_udpCtrl;
    QUdpSocket m_udpData;

public:
    explicit CNetworkSensorInterface (const QHostAddress &sensorIP,
                                      QObject *parent = nullptr,
                                      quint32 ctrl_port = 10001,
                                      quint32 data_port = 10000);
    ~CNetworkSensorInterface();

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
