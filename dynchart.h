#ifndef DYNCHART_H
#define DYNCHART_H

#include <QObject>
#include <QElapsedTimer>
#include <QDebug>
#include <QtCharts>

#include "grabapi.h"

class DynChart : public QObject {
    Q_OBJECT

public:
    DynChart(QChartView *view, QString title, std::string url, int numPoints = 60, int delay = 500, int numBlocks = 1);
    ~DynChart();

    QString getTitle();
    std::string getURL();

    int getNumPoints();
    int getDelay();
    int getNumBlocks();

public slots:
    void setPoints(std::vector<std::vector<double>> points);
    void removeFirst(qreal numPoints);
    void appendPoints(std::vector<std::vector<double>> points);

signals:
    void startAPI();
    void stopAPI();
    void deleteAPI();

private:
    void updateAxis();
    void removeDuplicatePoints(std::vector<std::vector<double>> *points);


    QThread thread;
    GrabApi *api;

    QChartView *view;
    QLineSeries *series;
    QChart *chart;

    QString title;
    std::string url;

    int maxBlocks;
    std::vector<int> blockSizes;

    int numPoints;
    int delay;
    int numBlocks;
};

#endif // DYNCHART_H


