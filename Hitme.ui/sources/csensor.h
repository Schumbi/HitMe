#ifndef CSENSOR_H
#define CSENSOR_H

#include <QObject>
#include <QUdpSocket>

class CSensor : public QObject {

    Q_OBJECT

private:
    QUdpSocket *ctrl;
    // QUdpSocket *data;

public:
    explicit CSensor (QObject *parent = nullptr);

    static constexpr quint32 ctrl_port = 10001;
    static constexpr quint32 data_port = 10000;

private slots:
    void readCtrlDatagram();
    //void readDataDatagram();


signals:
    void dataReceived (const QByteArray &datagram);

public slots:
    void sendData (const QByteArray &data);

};

#endif // CSENSOR_H
