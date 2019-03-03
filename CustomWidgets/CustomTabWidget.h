#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QTabWidget>

class CustomTabWidget : public QTabWidget
{
public:
    CustomTabWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CUSTOMTABWIDGET_H
