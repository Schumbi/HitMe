#include "hitmemainwindow.h"
#include "ui_hitmemainwindow.h"

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
    m_sensor1->setStarted (false);

    connect (m_sensor1, SIGNAL (statusUpdate()),
             this, SLOT (statusUpdate()));

    statusUpdate();

    connect (&updateTimer, &QTimer::timeout,
             this, &HitmeMainWindow::updateUI);

    connect (ui->checkBox_isOnline, &QCheckBox::stateChanged,
             this, &HitmeMainWindow::enableUIInput);

    updateTimer.setInterval (250);
    valuesToShow = 1000;
    updateTimer.start();
}

HitmeMainWindow::~HitmeMainWindow()
{
    if (m_sensor1 != nullptr)
    {
        delete  m_sensor1;
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

    Qt::CheckState checked = Qt::CheckState::Unchecked;

    if (m_sensor1->isOnline() && m_sensor1->isBMAOk())
    {
        checked = Qt::CheckState::Checked;
    }

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

    ui->checkBox_isOnline->setCheckState (checked);
}


void HitmeMainWindow::updateUI()
{
    if (accEnabled)
    {
        data_t toShow = m_sensor1->getLastValues (valuesToShow);
        m_accdisplay->setData (toShow);
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
