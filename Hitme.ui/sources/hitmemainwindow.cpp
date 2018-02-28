#include "hitmemainwindow.h"
#include "ui_hitmemainwindow.h"

#include "csensor.h"

HitmeMainWindow::HitmeMainWindow (QWidget *parent) :
    QMainWindow (parent), accEnabled (false),
    ui (new Ui::HitmeMainWindow)
{
    ui->setupUi (this);

    sensor1 = new CSensor (this);

    connect (ui->pushButton_startstop, &QPushButton::clicked, this,
             &HitmeMainWindow::activateMeasuring);

    connect (sensor1, &CSensor::dataReceived, ui->lineEdit_answer,
             &QLineEdit::setText);
}

HitmeMainWindow::~HitmeMainWindow()
{
    delete ui;
}

void HitmeMainWindow::getStatusMessage (const QByteArray &data)
{
    QString status (data);
    ui->lineEdit_answer->setText (status);
}

void HitmeMainWindow::activateMeasuring (bool val)
{
    Q_UNUSED (val);

    accEnabled = !accEnabled;

    if (accEnabled)
    {
        QString startstop ("{0:1}");
        sensor1->sendData (startstop.toLocal8Bit());
    }
    else
    {
        QString startstop ("{0:0}");
        sensor1->sendData (startstop.toLocal8Bit());
    }
}
