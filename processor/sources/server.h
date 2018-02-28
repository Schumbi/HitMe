#ifndef SERVER_H
#define SERVER_H

#include <QThread>
#include <QUdpSocket>
#include <QVector>
#include <QElapsedTimer>

#include "accdata.h"

class Server : public QThread {
    Q_OBJECT

    qint64 timeElapsed = 0;
    QElapsedTimer *tim;

    QVector<accData> dataVec;
    QUdpSocket *udpSocket;
    void processData (const QByteArray& data);

public:
    explicit Server (QObject *parent = nullptr);

signals:


public slots:
    void readingPendingDatagrams();
};

#endif // SERVER_H
