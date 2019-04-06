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
    SetLayout();
    SetStyleSheet();
}

void KeypadWidget::SetLayout()
{
    setFixedSize(300, 200);
    keyPadLayout = new QGridLayout();
    keyPadLayout->setSpacing(1);

    for(int i = 0; i < 10; i++){
        KeypadButton* button = new KeypadButton(i);
        keyPadLayout->addWidget(button, i / 3, i % 3);
        connect(button, SIGNAL(clicked(bool)), this, SLOT(DigitClicked(bool)));
    }
    QPushButton* button = new QPushButton("<");
    connect(button, SIGNAL(clicked(bool)), this, SLOT(CancelClicked(bool)));
    keyPadLayout->addWidget(button, 3, 1);

    button = new QPushButton("OK");
    connect(button, SIGNAL(clicked(bool)), this, SLOT(ConfirmClicked(bool)));
    connect(&confirmHighlightTimer, SIGNAL(timeout()), this, SLOT(ConfirmTimeout()));
    confirmHighlightTimer.setSingleShot(true);
    keyPadLayout->addWidget(button, 3, 2);

    passLineEdit = new QLineEdit();
    passLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
    passLineEdit->setReadOnly(true);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(passLineEdit);
    mainLayout->addLayout(keyPadLayout);
    mainLayout->addStretch();
}

void KeypadWidget::SetStyleSheet()
{
    QString style;
    style += "QLineEdit, QPushButton {height:40px; font:20px}";
    setStyleSheet(style);
}

void KeypadWidget::DigitClicked(bool clicked)
{
    Q_UNUSED(clicked);
    KeypadButton* key = reinterpret_cast<KeypadButton*>(sender());
    passLineEdit->setText(passLineEdit->text() + QString::number(key->GetKeyNumber()));
}

void KeypadWidget::ConfirmClicked(bool clicked )
{
    Q_UNUSED(clicked);
    if(passLineEdit->text().size() >= 4) {
        emit CodeEntered(passLineEdit->text());
        passLineEdit->clear();
    }
    else {
        styleSheet = passLineEdit->styleSheet();
        passLineEdit->setStyleSheet("QLineEdit {background:red}");
        confirmHighlightTimer.start(150);
    }
}

void KeypadWidget::CancelClicked(bool clicked)
{
    Q_UNUSED(clicked);
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

void KeypadWidget::ConfirmTimeout()
{
    passLineEdit->setStyleSheet(styleSheet);
}
