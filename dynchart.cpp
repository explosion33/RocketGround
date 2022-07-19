#include "dynchart.h"

DynChart::DynChart(QChartView *view, QString title, std::string url, int numPoints, int delay, int numBlocks)
{
    this->title = title;
    this->url = url;
    this->maxBlocks = numBlocks;

    this->numPoints = numPoints;
    this->delay = delay;
    this->numBlocks = numBlocks;

    this->view = view;
    this->chart = new QChart();
    this->series = new QLineSeries();

    this->series->setUseOpenGL(true);
    qDebug() << "using openGL: " << this->series->useOpenGL();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle(title);
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setPlotAreaBackgroundVisible(false);
    chart->setBackgroundVisible(false);

    // clear up old chart from heap after new one is added
    // program can crash if the current chart points to a deleted pointer
    // and setChart() is called
    QChart *old = view->chart();
    view->setChart(chart);
    delete old;


    view->setRenderHint(QPainter::Antialiasing);

    this->series->setColor(QColor(62, 96, 193, 255));
    chart->axes(Qt::Horizontal).back()->setLabelsBrush(QBrush(QColor(255,255,255,255)));
    chart->axes(Qt::Vertical).back()->setLabelsBrush(QBrush(QColor(255,255,255,255)));

    qRegisterMetaType<std::vector<std::vector<double>>>("std::vector<std::vector<double>>");

    this->api = new GrabApi(url, delay, true, numPoints);
    this->api->moveToThread(&this->thread);
    connect(this, SIGNAL(startAPI()), this->api, SLOT(start()));
    connect(this, SIGNAL(stopAPI()), this->api, SLOT(stop()));

    connect(this->api, SIGNAL(setPoints(std::vector<std::vector<double>>)),
            this, SLOT(setPoints(std::vector<std::vector<double>>)));

    connect(this->api, SIGNAL(appendPoints(std::vector<std::vector<double>>)),
            this, SLOT(appendPoints(std::vector<std::vector<double>>)));

    this->thread.start();
    emit startAPI();

}

QString DynChart::getTitle() {
    return this->title;
}

std::string DynChart::getURL() {
    return this->url;
}

DynChart::~DynChart() {
    qDebug() << "start of destructor";

    thread.terminate();

    delete this->series;

    thread.wait();
    qDebug() << "end of destructor";
}

void DynChart::setPoints(std::vector<std::vector<double>> points) {
    this->series->clear();

    this->appendPoints(points);

}

void DynChart::appendPoints(std::vector<std::vector<double>> points) {
    this->removeDuplicatePoints(&points);

    QList<QPointF> add;
    for (auto point : points) {
        qreal x = qreal(point[0]);
        qreal y = qreal(point[1]);
        QPointF p(x, y);
        add.append(p);
    }

    this->series->append(add);


    this->blockSizes.push_back(points.size());

    if (this->blockSizes.size() > (unsigned int)this->maxBlocks) {
        int num = this->blockSizes[0];


        this->blockSizes.erase(this->blockSizes.begin());

        this->removeFirst(num);
    }


    this->updateAxis();
}

void DynChart::updateAxis() {
    bool firstIter = true;
    qreal maxX = 0;
    qreal minX = 0;
    qreal maxY = 0;
    qreal minY = 0;
    for (auto point : this->series->pointsVector()) {
        qreal x = point.x();
        qreal y = point.y();

        if (firstIter) {
            maxX = x;
            minX = x;
            maxY = y;
            minY = y;
            firstIter = false;
        }
        else {
            if (x > maxX)
                maxX = x;
            if (x < minX)
                minX = x;
            if (y > maxY)
                maxY = y;
            if (y < minY)
                minY = y;
        }
    }

    qreal yRange = maxY - minY;
    if (yRange == 0) {
        yRange = 5;
    }
    minY -= yRange/10;
    maxY += yRange/10;


    this->chart->axes(Qt::Horizontal).back()->setRange(minX, maxX);
    this->chart->axes(Qt::Vertical).back()->setRange(minY, maxY);
}

void DynChart::removeDuplicatePoints(std::vector<std::vector<double>> *points) {
    auto currPoints = this->series->pointsVector();
    if (currPoints.size() == 0)
        return;

    qreal maxX = currPoints[currPoints.size()-1].x();
    int index = 0;
    for (auto point : *points) {
        qreal x = point[0];
        if (x <= maxX)
            index ++;
        else
            break;
    }

    points->erase(points->begin(), points->begin() + index);
}


void DynChart::removeFirst(qreal numPoints) {
    this->series->removePoints(0, numPoints);
}

int DynChart::getNumPoints() {
    return this->numPoints;
}
int DynChart::getDelay() {
    return this->delay;
}
int DynChart::getNumBlocks() {
    return this->numBlocks;
}
