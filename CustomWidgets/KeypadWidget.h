#ifndef KEYPADWIDGET_H
#define KEYPADWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>

#include "CustomWidgets/CustomTabWidget.h"
#include "CustomWidgets/KeypadButton.h"

class KeypadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeypadWidget(QWidget *parent = nullptr);

private:
    QGridLayout* keyPadLayout;
    QVBoxLayout* mainLayout;
    KeypadButton* buttonTab[12];
    QLineEdit* passLineEdit;
    QByteArray createHash(QString pin);

signals:

private slots:
    void keypadClicked(bool clicked);
    void confirm(bool clicked);
    void cancel(bool clicked);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // KEYPADWIDGET_H
