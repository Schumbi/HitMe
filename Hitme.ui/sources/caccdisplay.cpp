#include "caccdisplay.h"
#include "ui_caccdisplay.h"

CAccDisplay::CAccDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAccDisplay)
{
    ui->setupUi(this);
}

CAccDisplay::~CAccDisplay()
{
    delete ui;
}
