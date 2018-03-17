#ifndef CSIGNALPROCESSING_H
#define CSIGNALPROCESSING_H

#include <QObject>

class CSignalProcessing : public QObject
{
    Q_OBJECT
public:
    explicit CSignalProcessing(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CSIGNALPROCESSING_H