#ifndef LOGINTAB_H
#define LOGINTAB_H

#include <QWidget>
#include <QHBoxLayout>
#include <CustomWidgets/KeypadWidget.h>
#include <QLCDNumber>
#include "CustomWidgets/WeatherWidget.h"
#include <QLabel>
#include <QTimer>
#include <QSslError>
#include <QList>
#include <QNetworkReply>

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

    void SetLayout();
    void SetStylesheet();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void timeout();
    void SendCode(QString code);
};

#endif // LOGINTAB_H
