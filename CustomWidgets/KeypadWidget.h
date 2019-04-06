#ifndef KEYPADWIDGET_H
#define KEYPADWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTimer>

#include "CustomWidgets/CustomTabWidget.h"
#include "CustomWidgets/KeypadButton.h"

class KeypadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeypadWidget(QWidget *parent = nullptr);
    virtual ~KeypadWidget() override {}

private:
    QGridLayout* keyPadLayout;
    QVBoxLayout* mainLayout;
    KeypadButton* buttonTab[12];
    QLineEdit* passLineEdit;
    QTimer confirmHighlightTimer;
    QString styleSheet;

    void SetLayout();
    void SetStyleSheet();

signals:
    void CodeEntered(QString code);

private slots:
    void DigitClicked(bool clicked);
    void ConfirmClicked(bool clicked);
    void CancelClicked(bool clicked);
    void ConfirmTimeout();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // KEYPADWIDGET_H
