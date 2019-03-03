#include "CustomWidgets/CustomTabWidget.h"
#include <QtDebug>
#include <QStyleOption>
#include <QPainter>

CustomTabWidget::CustomTabWidget()
{
}

void CustomTabWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QTabWidget::paintEvent(event);
}
