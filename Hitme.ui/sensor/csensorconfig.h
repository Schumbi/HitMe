#ifndef CSENSORCONFIG_H
#define CSENSORCONFIG_H

#include <QString>

namespace sensor
{

class CSensorConfig
{
public:
    CSensorConfig()
    {
        ip = "192.168.1.7";
        udpControlPort = 10001;
        udpDataPort = 10000;
    }
    CSensorConfig ( const QString &ip,
                    quint32 controlPort = 10001,
                    quint32 dataPort = 10000 ) :
        ip ( ip ), udpControlPort ( controlPort ), udpDataPort ( dataPort )
    {}
    QString ip;
    quint32 udpControlPort;
    quint32 udpDataPort;
};

}

#endif // CSENSORCONFIG_H
