#include "WeatherWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>

WeatherWidget::WeatherWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("*{background:yellow}");
}

void WeatherWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QPixmap pixmap(":/img/resources/weather.png");
    painter.drawPixmap(0, 0, 300, 300, pixmap);
    QWidget::paintEvent(event);
}
