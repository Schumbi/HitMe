#ifndef CACCDISPLAY_H
#define CACCDISPLAY_H

#include <QWidget>

namespace Ui {
class CAccDisplay;
}

class CAccDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit CAccDisplay(QWidget *parent = 0);
    ~CAccDisplay();

private:
    Ui::CAccDisplay *ui;
};

#endif // CACCDISPLAY_H
