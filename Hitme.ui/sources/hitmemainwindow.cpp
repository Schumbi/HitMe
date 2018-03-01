#include "hitmemainwindow.h"
#include "ui_hitmemainwindow.h"

#include "cnetworksensorinterface.h"
#include "csensorctrlprocessor.h"

HitmeMainWindow::HitmeMainWindow (QWidget *parent) :
    QMainWindow (parent), accEnabled (false),
    ui (new Ui::HitmeMainWindow)
{
    ui->setupUi (this);

    m_ctrlProcessor = new CSensorCtrlProcessor (this);

    m_sensor1 = new CNetworkSensorInterface (QHostAddress ("192.168.1.5"), this);

    connect (m_sensor1, &CNetworkSensorInterface::udp_Ctrl_received,
             m_ctrlProcessor, &CSensorCtrlProcessor::processDatagram);

    connect (ui->pushButton_startstop, &QPushButton::clicked, this,
             &HitmeMainWindow::activateMeasuring);

    connect (m_ctrlProcessor, &CSensorCtrlProcessor::processedStatus,
             this, &HitmeMainWindow::getStatusMessage);

}

HitmeMainWindow::~HitmeMainWindow()
{
    delete ui;

    delete  m_ctrlProcessor;
    delete  m_sensor1;
}

void HitmeMainWindow::getStatusMessage (const CSensorStatus& status)
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
