#include "hitmemainwindow.h"
#include "ui_hitmemainwindow.h"

#include <csignalprocessing.h>

#include "caccdisplay.h"

#include <QLayout>
#include <QComboBox>
#include <QTimer>

HitmeMainWindow::HitmeMainWindow (QWidget *parent) :
    QMainWindow (parent), accEnabled (false),
    ui (new Ui::HitmeMainWindow)
{
    ui->setupUi (this);

    // add acc display
    m_accdisplay = new CAccDisplay ();
    QBoxLayout* layout = new QBoxLayout (QBoxLayout::LeftToRight) ;
    layout->addWidget (m_accdisplay);
    ui->accdata->setLayout (layout);

    enableUIInput (false);

    ui->pushButton_startstop->setText (QString ("Start"));

    m_sensor1 = new sensor::CSensor (sensor::CSensorConfig (
                                         QString ("192.168.1.7")), this);

    m_sigCalc = new signal::CSignalProcessing (this);
    m_sensor1->setStarted (false);

    connect (m_sensor1, SIGNAL (statusUpdate()),
             this, SLOT (statusUpdate()));

    statusUpdate();

    connect (&updateTimer, &QTimer::timeout,
             this, &HitmeMainWindow::updateUI);

    connect (ui->checkBox_isOnline, &QCheckBox::stateChanged,
             this, &HitmeMainWindow::enableUIInput);

    // ui update
    updateTimer.setInterval (50);
    valuesToShow = 5000;
    updateTimer.start();
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
        ui->lineEdit_answer->setText (msg);
        QTimer::singleShot (1000, this, SLOT (deleteMessages()));
    }
}


void HitmeMainWindow::updateUI()
{
    if (accEnabled)
    {
        data_t toShow = m_sensor1->getLastValues (valuesToShow);
        m_sigCalc->process (toShow);
        m_accdisplay->setData (toShow);
        QString msg = QString ("%1 %2").arg (toShow.size()).arg (
                          m_sensor1->getSizeOfStorage());
        ui->lineEdit_answer->setText (msg);
    }
    else
    {
        Qt::CheckState checked = Qt::CheckState::Unchecked;

        if (m_sensor1->isOnline())
        {
            checked = Qt::CheckState::Checked;
        }

        ui->checkBox_isOnline->setCheckState (checked);
    }
}

void HitmeMainWindow::on_pushButton_startstop_clicked()
{
    accEnabled = !accEnabled;
    m_sensor1->setStarted (accEnabled);

    if (accEnabled)
    {
        ui->pushButton_startstop->setText (QString ("Stop"));
    }
    else
    {
        ui->pushButton_startstop->setText (QString ("Start"));
    }
}

void HitmeMainWindow::on_comboBox_sensitivity_currentIndexChanged (int index)
{
    m_sensor1->setGRange (static_cast<sensor::GRange_e> (index));
}

void HitmeMainWindow::on_comboBox_bandwidth_currentIndexChanged (int index)
{
    m_sensor1->setBandWidth (static_cast<sensor::BandWidth_e> (index));
}

void HitmeMainWindow::enableUIInput (bool enable)
{
    ui->pushButton_startstop->setEnabled (enable);
    ui->comboBox_bandwidth->setEnabled (enable);
    ui->comboBox_sensitivity->setEnabled (enable);
}
