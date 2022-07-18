#include "led.h"

static const int LED_SIZE = 40;
static const QString GREEN = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:1, y2:1, stop:0 rgba(20, 252, 7, 255), stop:1 rgba(25, 134, 5, 255));").arg(LED_SIZE/2);
static const QString RED = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:0.92, y2:0.988636, stop:0 rgba(255, 12, 12, 255), stop:0.869347 rgba(103, 0, 0, 255));").arg(LED_SIZE/2);
static const QString GRAY = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.232, y1:0.272, x2:0.98, y2:0.959773, stop:0 rgba(113, 113, 113, 255), stop:1 rgba(41, 41, 41, 255))").arg(LED_SIZE/2);
static const QString BLUE = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.04, y1:0.0565909, x2:0.799, y2:0.795, stop:0 rgba(203, 220, 255, 255), stop:0.41206 rgba(0, 115, 255, 255), stop:1 rgba(0, 49, 109, 255));").arg(LED_SIZE/2);


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
