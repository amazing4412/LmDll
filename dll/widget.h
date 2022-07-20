#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
extern "C"{
#include "LmServerAPI.h"
}

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
