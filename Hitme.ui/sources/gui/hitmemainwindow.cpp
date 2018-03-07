#include "hitmemainwindow.h"
#include "ui_hitmemainwindow.h"

#include <cnetworksensorinterface.h>
#include <csensordatareceiver.h>
#include <csensorctrltransceiver.h>
#include "caccdisplay.h"

#include <QLayout>

HitmeMainWindow::HitmeMainWindow (QWidget *parent) :
    QMainWindow (parent), accEnabled (false),
    ui (new Ui::HitmeMainWindow)
{
    ui->setupUi (this);

    m_accdisplay = new CAccDisplay ();
    QBoxLayout* layout = new QBoxLayout (QBoxLayout::LeftToRight) ;
    layout->addWidget (m_accdisplay);
    ui->accdata->setLayout (layout);

    m_ctrlProcessor = new CSensorCtrlTransceiver (this);
    m_dataProcessor = new CSensorDataReceiver (this);

    m_sensor1 = new CNetworkSensorInterface (QHostAddress ("192.168.1.7"), this);

    // connect Network to control processor
    connect (m_sensor1, &CNetworkSensorInterface::udp_Ctrl_received,
             m_ctrlProcessor, &CSensorCtrlTransceiver::processDatagram);

    connect (m_sensor1, &CNetworkSensorInterface::udp_Data_received,
             m_dataProcessor, &CSensorDataReceiver::processDatagram);

    // output connection
    connect (m_ctrlProcessor, &CSensorCtrlTransceiver::processedStatus,
             this, &HitmeMainWindow::showStatusMessage);

    connect (m_dataProcessor, &CSensorDataReceiver::processedData,
             &m_storage, &CAccStorage::append);

    connect (&m_storage, &CAccStorage::gotPacket,
             this, &HitmeMainWindow::showData);

    // inputs to sensors
    connect (ui->pushButton_startstop, &QPushButton::clicked, this,
             &HitmeMainWindow::activateMeasuring);

}

HitmeMainWindow::~HitmeMainWindow()
{
    delete ui;

    delete  m_ctrlProcessor;
    delete  m_sensor1;
}

void HitmeMainWindow::showStatusMessage (const CSensorStatus& status)
{
    ui->label_sensorIP->setText (status.fromIp());
    ui->checkBox_isOnline->setChecked (status.state() == CSensorStatus::OK);
    ui->lineEdit_answer->setText (status.message());
}

void HitmeMainWindow::activateMeasuring (bool val)
{
    Q_UNUSED (val);

    accEnabled = !accEnabled;

    if (accEnabled)
    {
        QString startstop ("{0:1}");
        m_sensor1->sendCommandToSensor (startstop.toLocal8Bit());
    }
    else
    {
        QString startstop ("{0:0}");
        m_sensor1->sendCommandToSensor (startstop.toLocal8Bit());
    }
}

void HitmeMainWindow::showData (quint64 pkg)
{
    Q_UNUSED (pkg);
    m_accdisplay->setData (m_storage.storage());
}
