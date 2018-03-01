#ifndef CSENSORSTATUS_H
#define CSENSORSTATUS_H

#include <QString>
#include <QMetaType>

class CSensorStatus {
public:

    enum e_sensorstate
    {
        OK,
        ERR
    };

    CSensorStatus ();
    CSensorStatus (const CSensorStatus &other);
    ~CSensorStatus();


    CSensorStatus (const QString& ip,
                   const e_sensorstate& state,
                   const QString& msg);

    e_sensorstate state() const;
    QString fromIp() const;
    QString message() const;

    void set_fromIp (const QString &fromIp);
    void set_message (const QString &msg);
    void set_state (const e_sensorstate& state);


private:
    e_sensorstate m_state;
    QString m_ip;
    QString m_message;
};

Q_DECLARE_METATYPE (CSensorStatus);

QDebug operator<< (QDebug dbg, const CSensorStatus &message);

#endif // CSENSORSTATUS_H
