#include "csignalmaxrecorder.h"

#include <QDateTime>

using namespace signal;

int CSignalMaxRecorder::maxCtr() const
{
    return m_maxCtr;
}

void CSignalMaxRecorder::setMaxCtr (int maxCtr)
{
    m_maxCtr = maxCtr;
}

CSignalMaxRecorder::CSignalMaxRecorder (CSignalProcessing *p)
    : CAbstractProcessor (p)
{}

bool gtTresh (const QVector4D &data, int thresh)
{
    return qAbs (data.x()) > thresh ||
           qAbs (data.y()) > thresh ||
           qAbs (data.z()) > thresh;
}

void writeToFile (const data_t &data)
{
    QDate d = QDate::currentDate();
    QTime t = QTime::currentTime();

    QString dt = QString ("%1_%2")
                 .arg (d.toString (Qt::DateFormat::ISODate))
                 .arg (t.toString (Qt::DateFormat::ISODate));

    QFile file (dt + QString ("_%1")
                .arg (static_cast<quint64> (data.at (0).w())));

    if (!file.open (QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out (&file);

    for (int ctr = 0; ctr < data.size(); ctr++)
    {
        auto c = data[ctr];
        out << static_cast<quint64> (c.w()) << ","
            << c.x() << ","
            << c.y() << ","
            << c.z() << ';'
            << '\n';
    }

    out.flush();
    file.close();
}

void CSignalMaxRecorder::changeData (data_t &data)
{
    if (!data.size())
    {
        return;
    }

    const int pkgSize = m_pkgSize; // number of acc values per paket from sensor
    const int thresh = m_threshold; // threshold
    bool hasMax = false;

    int mid = data.size() / 2;

    if (gtTresh (data[mid], thresh ))
    {
        for (int ctr = mid;
                (ctr < data.size() - m_maxCtr) &&
                (ctr < mid + pkgSize);
                ctr++)
        {
            hasMax = true;

            for (int ictr = 0; ictr < m_maxCtr; ictr++)
            {
                hasMax &= gtTresh (data.at (ctr + ictr), thresh);
            }
        }
    }

    if (hasMax == true)
    {
        writeToFile (data);
    }
}
