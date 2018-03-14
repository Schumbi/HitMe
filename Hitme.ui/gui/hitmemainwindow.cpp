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

    m_sensor1 = new sensor::CSensor (sensor::CSensorConfig (
                                         QString ("192.168.1.5")), this);
    connect (m_sensor1, SIGNAL (statusUpdate()),
             this, SLOT (statusUpdate()));

    statusUpdate();
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

void HitmeMainWindow::on_pushButton_startstop_clicked()
{
    bool started = m_sensor1->sensorStarted();
    m_sensor1->setStarted (!started);

    started = m_sensor1->sensorStarted();

    if (started)
    {
        ui->pushButton_startstop->setText (QString ("started"));
    }
    else
    {
        ui->pushButton_startstop->setText (QString ("stoped"));
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
