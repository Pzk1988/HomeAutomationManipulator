#ifndef KEYPADBUTTON_H
#define KEYPADBUTTON_H

#include<QPushButton>

class KeypadButton : public QPushButton
{
public:
    KeypadButton(int number, QWidget *parent = nullptr);
    int GetKeyNumber();

private:
    int number;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // KEYPADBUTTON_H
