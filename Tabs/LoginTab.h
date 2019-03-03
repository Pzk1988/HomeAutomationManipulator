#ifndef LOGINTAB_H
#define LOGINTAB_H

#include <QWidget>
#include <QHBoxLayout>
#include <CustomWidgets/KeypadWidget.h>
#include <QLCDNumber>
#include "CustomWidgets/WeatherWidget.h"
#include <QLabel>
#include <QTimer>

class LoginTab : public QWidget
{
    Q_OBJECT
public:
    explicit LoginTab(QWidget *parent = nullptr);

signals:

public slots:
private:
    QHBoxLayout mainLayout;
    KeypadWidget keyPad;
    QLabel clockLabel;
    QLabel dateLabel;
    QGridLayout leftLayout;
    WeatherWidget* weatherWidget;
    QTimer timer;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void timeout();
};

#endif // LOGINTAB_H
