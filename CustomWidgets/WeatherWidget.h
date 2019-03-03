#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>

class WeatherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WeatherWidget(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // WEATHERWIDGET_H
