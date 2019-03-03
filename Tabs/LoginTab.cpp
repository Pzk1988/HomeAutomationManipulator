#include "LoginTab.h"
#include <QDebug>
#include <QLineEdit>
#include <QDateTime>
#include <QStyleFactory>
#include <QStyleOption>
#include <QPainter>
#include <QFontDatabase>

LoginTab::LoginTab(QWidget *parent) : QWidget(parent)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    clockLabel.setText(currentTime.toString("HH:MM:ss - dd.MM.yyyy"));
    clockLabel.setFixedHeight(50);

    dateLabel.setText("Disconnected");

    weatherWidget = new WeatherWidget(this);

    leftLayout.addWidget(&clockLabel, 0, 0);
    leftLayout.addWidget(&dateLabel, 0, 1);
    leftLayout.addWidget(weatherWidget, 1, 0, 1, 2);

    mainLayout.addLayout(&leftLayout);
    mainLayout.addWidget(&keyPad);
    setLayout(&mainLayout);

    timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer.start();

    setStyleSheet("QLabel {font-size: 16px;}");
}

void LoginTab::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}

void LoginTab::timeout()
{
    clockLabel.setText(QDateTime::currentDateTime().toString("HH:MM:ss - dd.MM.yyyy"));
}
