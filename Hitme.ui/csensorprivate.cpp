#include "csensorprivate.h"

#include "csensor.h"

#include <QNetworkDatagram>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

namespace sensor {

static quint16 g_id = 0;

bool tryGetValue (const QString &key, QJsonValue &val,
                  const QJsonObject &o)
{
    val = o[key];
    return val.type() != QJsonValue::Undefined;
}

CSensorPrivate::CSensorPrivate (const QString &ip,
                                quint32 controlPort,
                                quint32 dataPort,
                                CSensor *p,
                                QObject *parent)
    : QObject (parent), p (p),
      m_bmaReadable (false), m_id (g_id++),
      m_controlPort (controlPort),
      m_dataPort (dataPort), m_ip (ip)
{
    m_controlSocket = new QUdpSocket (this);
    m_dataSocket = new QUdpSocket (this);
    // connect (listen to ports for udp packages)
    reconnect();
}

bool CSensorPrivate::reconnect()
{
    bool bound;

    m_startSensor = false;

    // reconnect udp control socket
    if (m_controlSocket->isOpen())
    {
        m_controlSocket->disconnect();
        m_controlSocket->close();
    }

    bound = m_controlSocket->bind (QHostAddress::AnyIPv4, m_controlPort);

    // reconnect udp data socket
    if (m_dataSocket->isOpen())
    {
        m_dataSocket->close();
    }

    bound &= m_dataSocket->bind (QHostAddress::AnyIPv4, m_dataPort);

    m_connected = bound;
    emit connected (m_connected);

    if (bound)
    {
        connect (m_controlSocket, &QUdpSocket::readyRead,
                 this, &CSensorPrivate::gotCtrlPackage);
        connect (m_dataSocket, &QUdpSocket::readyRead,
                 this, &CSensorPrivate::gotDataPackage);
    }

    return bound;
}

void CSensorPrivate::gotCtrlPackage()
{
    while (m_controlSocket->hasPendingDatagrams())
    {

        QNetworkDatagram datagram =  m_controlSocket->receiveDatagram();

        if (datagram.senderAddress().toString() == this->ip())
        {
            processCtrlPackage (datagram.data());
        }
    }
}

void CSensorPrivate::gotDataPackage()
{
    while (m_dataSocket->hasPendingDatagrams())
    {

        QNetworkDatagram datagram =  m_dataSocket->receiveDatagram();

        if (datagram.senderAddress().toString() == this->ip())
        {
            processDataPackage (datagram.data());
        }
    }
}


quint16 CSensorPrivate::id() const
{
    return m_id;
}

QString CSensorPrivate::ip() const
{
    return m_ip;
}

BMA020BANDWIDTH CSensorPrivate::bw() const
{
    return m_bandwidth;
}

void CSensorPrivate::setBW (BMA020BANDWIDTH val)
{
    m_bandwidth = val;
    createCtrlPackage();
}

BMA020RANGE CSensorPrivate::range() const
{
    return m_range;
}

void CSensorPrivate::setRange (BMA020RANGE val)
{
    m_range = val;
    createCtrlPackage();
}

bool CSensorPrivate::startedSensor() const
{
    return m_startSensor;
}

void CSensorPrivate::setStartSensor (bool start)
{
    m_startSensor = start;
    createCtrlPackage();

    if (start == false)
    {
        int wanted = m_storage.size();
        m_storage.storage().clear();
        m_storage.storage().reserve (wanted);
    }
}

bool CSensorPrivate::tryReconnect (const QString &ip)
{
    m_ip = ip;
    return reconnect();
}

bool CSensorPrivate::isConnected() const
{
    return m_connected;
}

bool CSensorPrivate::isBMAreadable()
{
    return m_bmaReadable;
}

QString CSensorPrivate::lastErr()
{
    return m_errMsg;
}

QString CSensorPrivate::lastMsg()
{
    return m_msg;
}

void CSensorPrivate::deleteMessages()
{
    if (lastErr().isEmpty() == false)
    {
        lastErr().clear();
        return;
    }

    if (lastMsg().isEmpty() == false)
    {
        lastMsg().clear();
        return;
    }
}

void CSensorPrivate::createCtrlPackage()
{
    QJsonObject o;
    o[JKEY_type] = MSGTYPE::REQUEST;
    o[JKEY_range] = static_cast<int> (this->range());
    o[JKEY_bandwidth] = static_cast<int> (this->bw());
    o[JKEY_start] = static_cast<bool> (this->startedSensor());
    o[JKEY_cmd] = static_cast<int> (-1);

    QByteArray ar = QJsonDocument (o).toJson (QJsonDocument::Compact);
    sendCtrlPkg (ar);
}

data_t CSensorPrivate::getLastValues (int count)
{
    data_t res;
    return m_storage.getLastValues (count);
}

void CSensorPrivate::sendCtrlPkg (const QByteArray& data)
{
    QNetworkDatagram datagram;
    datagram.setDestination (QHostAddress (ip()), m_controlPort);
    datagram.setData (data);
    m_dataSocket->writeDatagram (datagram);
}

bool CSensorPrivate::processStatusMessage (const QJsonObject &o)
{
    QJsonValue val;

    bool parsable = tryGetValue (JKEY_readable, val, o);

    if (parsable)
    {
        m_bmaReadable = val.toBool (false);
    }

    parsable &= tryGetValue (JKEY_bandwidth, val, o);

    if (parsable)
    {
        m_bandwidth = static_cast<BMA020BANDWIDTH> (val.toInt (0));
    }

    parsable &= tryGetValue (JKEY_range, val, o);

    if (parsable)
    {
        m_range = static_cast<BMA020RANGE> (val.toInt (0));
    }

    parsable &= tryGetValue (JKEY_millis, val, o);

    if (parsable)
    {
        m_millis = val.toInt (0);
    }

    return parsable;
}

bool CSensorPrivate::processAnswer (const QJsonObject &o)
{
    QJsonValue val;

    m_answer_cmd = "";
    m_answer_cmd_arg = "";
    m_errMsg = "";
    m_cmdError = false;
    m_msg = "";
    m_ret = "";

    bool parsable = tryGetValue (JKEY_cmd, val, o);

    if (parsable)
    {
        m_answer_cmd = val.toString ("");
    }

    parsable &= tryGetValue (JKEY_err, val, o);

    if (parsable)
    {
        m_errMsg = val.toString ("");
        m_cmdError = m_errMsg.size() > 0;
    }

    parsable &= tryGetValue (JKEY_msg, val, o);

    if (parsable)
    {
        m_msg = val.toString ("");
    }

    parsable &= tryGetValue (JKEY_ret, val, o);

    if (parsable)
    {
        m_ret = val.toString ("");
    }

    return parsable;
}

void CSensorPrivate::processCtrlPackage (const QByteArray &data)
{
    QJsonParseError jerror;
    QJsonDocument jdoc = QJsonDocument::fromJson (data, &jerror);

    if (jdoc.isNull())
    {
        emit ctrlParseError (jerror.errorString());
        return;
    }

    QJsonObject o = jdoc.object();
    QJsonValue val;

    if (tryGetValue (JKEY_type, val, o))
    {
        sensor::MSGTYPE typesID =
            static_cast<sensor::MSGTYPE> (val.toInt (sensor::MSGTYPE::PARSEERR));

        if (typesID == sensor::MSGTYPE::STATUS ||
                typesID == sensor::MSGTYPE::ANSWER)
        {
            this->processStatusMessage (o);
        }

        if (typesID == sensor::MSGTYPE::ANSWER)
        {
            this->processAnswer (o);
        }

        emit p->statusUpdate();
    }
}

void sensor::CSensorPrivate::processDataPackage (const QByteArray &data)
{
    m_storage.addRawData (data);
    emit dataParsed();
}
} // ns sensor

