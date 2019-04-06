#include "LoginTab.h"
#include <QDebug>
#include <QLineEdit>
#include <QDateTime>
#include <QStyleFactory>
#include <QStyleOption>
#include <QPainter>
#include <QFontDatabase>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QSslConfiguration>
#include <QJsonDocument>

LoginTab::LoginTab(QWidget *parent) : QWidget(parent)
{
    SetLayout();
    SetStylesheet();
}

void LoginTab::SetLayout()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    clockLabel.setText(currentTime.toString("HH:mm:ss - dd.MM.yyyy"));
    clockLabel.setFixedHeight(50);

    dateLabel.setText("Disconnected");

    weatherWidget = new WeatherWidget(this);

    leftLayout.addWidget(&clockLabel, 0, 0);
    leftLayout.addWidget(&dateLabel, 0, 1);
    leftLayout.addWidget(weatherWidget, 1, 0, 1, 2);

    mainLayout.addLayout(&leftLayout);
    mainLayout.addWidget(&keyPad);
    connect(&keyPad, SIGNAL(CodeEntered(QString)), this, SLOT(SendCode(QString)));
    setLayout(&mainLayout);

    timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer.start();
}

void LoginTab::SetStylesheet()
{
    QString style;
    style += "QLabel {font-size: 16px;}";
    setStyleSheet(style);
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
    clockLabel.setText(QDateTime::currentDateTime().toString("HH:mm:ss - dd.MM.yyyy"));
}

void LoginTab::SendCode(QString code)
{
    qDebug() << "Code: " + code;

    QUrl myurl;
    myurl.setScheme("https"); //https also applicable
    myurl.setHost("192.168.1.3");
    myurl.setPort(8443);
    myurl.setPath("/Alarm");

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *reply = NULL;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonObj;
    jsonObj.insert("id", code);
    QJsonDocument doc(jsonObj);
    reply = manager->post(request, doc.toJson());
}


//QString KeypadWidget::createHash(QString pin)
//{
//    QByteArray array;
//    for(int i = 0; i < pin.size(); i++)
//    {
//        array.append(pin.at(i));
//    }

//    QCryptographicHash hash(QCryptographicHash::Md4);
//    hash.addData(array);
//    QByteArray result = hash.result();

//    return result;
//}

//QUrl myurl;
//myurl.setScheme("http"); //https also applicable
//myurl.setHost("192.168.1.2");
//myurl.setPort(8080);
//myurl.setPath("/Alarm");

//QNetworkAccessManager *manager = new QNetworkAccessManager();
//QNetworkRequest request;
//QNetworkReply *reply = NULL;

//request.setUrl(myurl);
//request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//QJsonObject jsonObj;
//jsonObj.insert("id", createHash(passLineEdit->text()));
//QJsonDocument doc(jsonObj);
//reply = manager->post(request, doc.toJson());
//passLineEdit->clear();
