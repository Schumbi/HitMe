#include "hitmemainwindow.h"
#include "ui_hitmemainwindow.h"

#include <csignalprocessing.h>

#include "caccdisplay.h"

#include <QLayout>
#include <QComboBox>
#include <QTimer>

HitmeMainWindow::HitmeMainWindow (QWidget *parent) :
    QMainWindow (parent),
    calibrating (false),
    accEnabled (false),
    ui (new Ui::HitmeMainWindow)
{
    ui->setupUi (this);

    // add acc display
    m_accdisplay = new CAccDisplay ();
    QBoxLayout* layout = new QBoxLayout (QBoxLayout::LeftToRight) ;
    layout->addWidget (m_accdisplay);
    ui->accdata->setLayout (layout);

    ui->pushButton_startstop->setText (QString ("Start"));

    m_sensor1 = new sensor::CSensor (sensor::CSensorConfig (
                                         QString ("192.168.1.7")), this);

    m_sigCalc = new signal::CSignalProcessing (this);
    m_sensor1->setStarted (false);

    connect (m_sensor1, &sensor::CSensor::statusUpdate,
             this, &HitmeMainWindow::statusUpdate);
    connect (m_sensor1, &sensor::CSensor::connected,
             this, &HitmeMainWindow::enableUIInput);

    connect (m_sigCalc, &signal::CSignalProcessing::calibrated,
             this, &HitmeMainWindow::calibratedData);

    statusUpdate();

    connect (&updateTimer, &QTimer::timeout,
             this, &HitmeMainWindow::updateUI);

    // ui update
    updateTimer.setInterval (0);
    valuesToShow = 15000;
    updateTimer.start();
    ui->spinBox_duration->setValue (valuesToShow / 1000);
    ui->spinBox_duration->setMaximum (
        m_sensor1->getStorage().getMaxmeasurementtime_Sec());

    enableUIInput (false);
}

HitmeMainWindow::~HitmeMainWindow()
{
    if (m_sensor1 != nullptr)
    {
        delete  m_sensor1;
    }

    if (m_sigCalc != nullptr)
    {
        delete m_sigCalc;
    }

    delete ui;
}

void HitmeMainWindow::deleteMessages()
{
    m_sensor1->deleteMessages();
}

void HitmeMainWindow::statusUpdate()
{
    ui->comboBox_bandwidth->setCurrentIndex (static_cast<int>
            (m_sensor1->bandwidth()));

    ui->comboBox_sensitivity->setCurrentIndex (static_cast<int>
            (m_sensor1->range()));

    ui->label_sensorIP->setText (m_sensor1->ip());

    QString msg = m_sensor1->sensorErr();

    if (msg.isEmpty())
    {
        msg = m_sensor1->sensorMsg();
    }

    if (msg.isEmpty() == false)
    {
        QTimer::singleShot (1000, this, SLOT (deleteMessages()));
    }
}

void HitmeMainWindow::updateUI()
{
    if (accEnabled)
    {
        double fac = 1.0;
        double min = 0.0;
        double max = 1.0;

        switch (m_sensor1->range())
        {
        // 512 => 2g
        case sensor::GRange_e::G2:
            fac = 2 / ((1024 / 2.0));
            max = 2.0;
            break;

        // 512 => 4g
        case sensor::GRange_e::G4:
            fac = 4 / ((1024 / 2.0));
            max = 4.0;
            break;

        // 512 => 8g
        case sensor::GRange_e::G8:
            fac = 8 / ((1024 / 2.0));
            max = 8.0;
            break;

        }

        m_sigCalc->setConversionFactor (fac);
        // retrieve data from sensor
        data_t toShow = m_sensor1->getLastValues (valuesToShow);

        diff.append (m_sensor1->getStorage().getPkgtimeDiff());
        double middle = 0;

        foreach (auto val, diff)
        {
            middle += val;
        }

        middle /= diff.size();

        if (diff.size() >= 1000)
        {
            diff.removeFirst();
        }


        ui->label_debMsg->setText (QString ("m: %1 pd: %2")
                                   .arg (qRound (middle / 1000.0))
                                   .arg (m_sensor1->getStorage().getPCtrDiff()));

        // process date
        m_sigCalc->process (toShow);

        double maxx = m_sigCalc->maxValue().x();
        ui->lcdNumber_maxForce->display (maxx);

        // show data
        m_accdisplay->setData (toShow, min, max);
    }

    ui->pushButton_calibration->setEnabled (accEnabled);

    if (accEnabled)
    {
        ui->pushButton_startstop->setText (QString ("Stop"));
    }
    else
    {
        ui->pushButton_startstop->setText (QString ("Start"));
    }
}

void HitmeMainWindow::on_pushButton_startstop_clicked()
{
    accEnabled = !accEnabled;
    m_sensor1->setStarted (accEnabled);
}

void HitmeMainWindow::on_comboBox_sensitivity_currentIndexChanged (int index)
{
    stopSensor();
    m_sensor1->setGRange (static_cast<sensor::GRange_e> (index));
}

void HitmeMainWindow::on_comboBox_bandwidth_currentIndexChanged (int index)
{
    stopSensor();
    m_sensor1->setBandWidth (static_cast<sensor::BandWidth_e> (index));
}

void HitmeMainWindow::enableUIInput (bool enable)
{
    ui->frame_sensorSettings->setEnabled (enable);
    ui->pushButton_startstop->setEnabled (enable);
    ui->comboBox_bandwidth->setEnabled (enable);
    ui->comboBox_sensitivity->setEnabled (enable);
}

void HitmeMainWindow::calibratedData (QVector3D biases)
{
    m_dataBias = biases;
}

void HitmeMainWindow::on_pushButton_calibration_clicked()
{
    startCalibration();
}

void HitmeMainWindow::stopSensor()
{
    accEnabled = false;
    m_sensor1->setStarted (false);
}

void HitmeMainWindow::startSensor()
{
    accEnabled = true;
    m_sensor1->setStarted (true);
}

void HitmeMainWindow::stopCalibration()
{
    calibrating = false;
    m_sigCalc->setCalibrating (calibrating);
    this->enableUIInput (true);
}

void HitmeMainWindow::startCalibration()
{
    if (calibrating == false)
    {
        calibrating = true;
    }

    m_sigCalc->setCalibrating (true);
    QTimer::singleShot (5000, this, SLOT (stopCalibration()));

    this->enableUIInput (false);
}

void HitmeMainWindow::on_spinBox_duration_valueChanged (int numToShow)
{
    valuesToShow = numToShow * 1000;

}
