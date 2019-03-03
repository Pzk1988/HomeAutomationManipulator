#include "CustomWidgets/KeypadWidget.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCryptographicHash>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

KeypadWidget::KeypadWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300, 200);
    keyPadLayout = new QGridLayout();
    keyPadLayout->setSpacing(1);

    for(int i = 0; i < 10; i++){
        KeypadButton* button = new KeypadButton(i);
        keyPadLayout->addWidget(button, i / 3, i % 3);
        connect(button, SIGNAL(clicked(bool)), this, SLOT(keypadClicked(bool)));
    }
    QPushButton* button = new QPushButton("<");
    connect(button, SIGNAL(clicked(bool)), this, SLOT(cancel(bool)));
    keyPadLayout->addWidget(button, 3, 1);

    button = new QPushButton("OK");
    connect(button, SIGNAL(clicked(bool)), this, SLOT(confirm(bool)));
    keyPadLayout->addWidget(button, 3, 2);

    passLineEdit = new QLineEdit();
    passLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
    passLineEdit->setReadOnly(true);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(passLineEdit);
    mainLayout->addLayout(keyPadLayout);
    mainLayout->addStretch();

    setStyleSheet("QLineEdit, QPushButton {height:40px; font:20px}");
}

void KeypadWidget::keypadClicked(bool clicked)
{
    KeypadButton* key = reinterpret_cast<KeypadButton*>(sender());
    qDebug() << key->GetKeyNumber();
    passLineEdit->setText(passLineEdit->text() + QString::number(key->GetKeyNumber()));
}

void KeypadWidget::confirm(bool clicked)
{
    QUrl myurl;
    myurl.setScheme("http"); //https also applicable
    myurl.setHost("192.168.1.2");
    myurl.setPort(8080);
    myurl.setPath("/Alarm");

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *reply = NULL;

    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonObj;
    jsonObj.insert("id", "wynik");
    QJsonDocument doc(jsonObj);
    reply = manager->post(request, doc.toJson());
    passLineEdit->clear();
}

void KeypadWidget::cancel(bool clicked)
{
    QString text = passLineEdit->text();
    if(text.length() > 0)
    {
        text.remove(text.length() - 1, 1);
        passLineEdit->setText(text);
    }
}

void KeypadWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QWidget::paintEvent(event);
}

QByteArray KeypadWidget::createHash(QString pin)
{
    QByteArray array;
    for(int i = 0; i < pin.size(); i++)
    {
        array.append(pin.at(i));
    }

    QCryptographicHash hash(QCryptographicHash::Md4);
    hash.addData(array);
    return hash.result();
}
