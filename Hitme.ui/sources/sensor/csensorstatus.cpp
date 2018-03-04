#include "csensorstatus.h"

#include <QDebug>

CSensorStatus::CSensorStatus()
{
}

CSensorStatus::CSensorStatus (const CSensorStatus& other)
{
    m_ip = other.m_ip;
    m_message = other.m_message;
    m_state = other.m_state;
}

CSensorStatus::~CSensorStatus ()
{
}

CSensorStatus::CSensorStatus (const QString &ip,
                              const CSensorStatus::e_sensorstate &state,
                              const QString &msg)
    : m_state (state), m_ip (ip),  m_message (msg)
{

}

void CSensorStatus::set_fromIp (const QString &ip)
{
    m_ip = ip;
}

void CSensorStatus::set_message (const QString &msg)
{
    m_message = msg;
}

void CSensorStatus::set_state (const CSensorStatus::e_sensorstate &state)
{
    m_state = state;
}

CSensorStatus::e_sensorstate CSensorStatus::state() const
{
    return m_state;
}

QString CSensorStatus::fromIp() const
{
    return m_ip;
}

QString CSensorStatus::message() const
{
    return m_message;
}

QDebug operator<< (QDebug dbg, const CSensorStatus &sensorStatus)
{
    dbg.nospace() << "CSensorStatus() from IP:" << sensorStatus.fromIp()
                  << " state: " << (sensorStatus.state() == CSensorStatus::e_sensorstate::OK ?
                                    "OK" : "NOK" )
                  << " msg: " << sensorStatus.message();
    return dbg.maybeSpace();
}



