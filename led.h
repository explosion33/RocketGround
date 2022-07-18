#ifndef LED_H
#define LED_H

#include <QtConcurrent/QtConcurrent>
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>

#include "grabapi.h"


class LED : public QLabel
{
    Q_OBJECT
public:
    explicit LED(QWidget *parent = nullptr, std::string url="", int delay=500);
    ~LED();

    QString getUrl();
    int getDelay();

    enum State{
            Gray,
            Green,
            Red,
            Blue,
        };

private:
    QThread thread;
    GrabApi *api;

    std::string url;
    int delay;

public slots:
    void setState(State state);
    void setValue(std::vector<std::vector<double>> points);

signals:
    void startAPI();

};

#endif // LED_H
