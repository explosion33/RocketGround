#include "led.h"

static const int LED_SIZE = 60;
static const QString GREEN = QString("color: white;border-radius: %1; border: 1px solid #999999 background-color: rgba(62, 96, 193, 0)").arg(LED_SIZE/2);
static const QString RED = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:0.92, y2:0.988636, stop:0 rgba(255, 12, 12, 255), stop:0.869347 rgba(103, 0, 0, 255));").arg(LED_SIZE/2);
static const QString GRAY = QString("border-radius: %1; border: 4px solid #999999; background-color: rgba(62, 96, 193, 0);").arg(LED_SIZE/2);
static const QString BLUE = QString("color: white;border-radius: %1; border: 4px solid rgba(62, 96, 193, 255); background-color: rgba(62, 96, 193, 67);").arg(LED_SIZE/2);


LED::LED(QWidget *parent, std::string url, int delay) : QLabel(parent)
{

    setFixedSize(LED_SIZE, LED_SIZE);
    setState(LED::State::Gray);

    this->url = url;
    this->delay = delay;

    qRegisterMetaType<std::vector<std::vector<double>>>("std::vector<std::vector<double>>");

    this->api = new GrabApi(url, delay, true, 2);
    this->api->moveToThread(&this->thread);
    connect(this, SIGNAL(startAPI()), this->api, SLOT(start()));

    connect(this->api, SIGNAL(appendPoints(std::vector<std::vector<double>>)),
            this, SLOT(setValue(std::vector<std::vector<double>>)));

    this->thread.start();
    emit startAPI();

    this->show();

}

void LED::setValue(std::vector<std::vector<double>> points) {
    if (points.size() == 0)
        return;

    int latest_val = (int)(points[0][1]);
    this->setState(static_cast<State>(latest_val));
}

LED::~LED() {
    thread.terminate();
    thread.wait();
}

void LED::setState(State state) {
    switch (state) {
        case Gray:
            this->setStyleSheet(GRAY);
        break;
        case Blue:
            this->setStyleSheet(BLUE);
        break;
        case Green:
            this->setStyleSheet(GREEN);
        break;
        case Red:
            this->setStyleSheet(RED);
        break;
    }
}

QString LED::getUrl() {
    return QString::fromStdString(this->url);
}
int LED::getDelay() {
    return this->delay;
}
