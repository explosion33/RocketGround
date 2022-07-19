#ifndef GRABAPI_H
#define GRABAPI_H

#include <QObject>
#include <QElapsedTimer>
#include <QDebug>

#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include <curl/curl.h>


class GrabApi : public QObject {
    Q_OBJECT

public:
    static QStringList acceptedInputs;
    static QStringList acceptedOutputs;


    GrabApi(std::string url, int delay = 500, bool rolling = false, int numPoints=15);
    ~GrabApi();

    static size_t curlWriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
    static std::string request(std::string url);
    static std::vector<std::vector<double>> parseList(std::string data);


signals:
    void setPoints(std::vector<std::vector<double>> points);
    void addPoint(qreal, qreal);
    void appendPoints(std::vector<std::vector<double>> points);

public slots:
    void start();
    void stop();

private:
    std::string url;
    int delay;
    int size;
    bool rolling;
    int numPoints;
};


#endif // GRABAPI_H
