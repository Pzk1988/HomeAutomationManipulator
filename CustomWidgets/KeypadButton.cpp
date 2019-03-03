#include "CustomWidgets/KeypadButton.h"
#include <QPainter>
#include <QStyleOption>

KeypadButton::KeypadButton(int number, QWidget *parent) : QPushButton (QString::number(number), parent)
{
    this->number = number;
}

int KeypadButton::GetKeyNumber()
{
    return number;
}

void KeypadButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QPushButton::paintEvent(event);
}
