#ifndef SERVER_H
#define SERVER_H

#include <QThread>
#include <QUdpSocket>
#include <QVector>
#include <QElapsedTimer>

#include "accdata.h"

class AccDataReceiver : public QThread {
    Q_OBJECT

    qint64 timeElapsed = 0;
    QElapsedTimer *tim;

    QVector<int> dataVec;
    QUdpSocket *udpSocket;
    void processData (const QByteArray& data);

public:
    explicit AccDataReceiver (QObject *parent = nullptr);

signals:
    void dataReady (QVector<int>vec);


public slots:
    void readingPendingDatagrams();
};

#endif // SERVER_H
