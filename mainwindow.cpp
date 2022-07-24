#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    ui->setupUi(this);

    this->dchart1 = nullptr;
    this->dchart2 = nullptr;
    this->dchart3 = nullptr;
    this->dchart4 = nullptr;

    this->led1 = nullptr;
    this->led2 = nullptr;

    this->settingsPopUp = new Settings();

    qRegisterMetaType<std::map<QString,QString>>("std::map<QString,QString>");
    connect(ui->settings, SIGNAL(clicked()), this, SLOT(showSettings()));
    connect(this->settingsPopUp, SIGNAL(settingsChanged(std::map<QString,QString>)),
            this, SLOT(updateCharts(std::map<QString,QString>)));
    connect(this->settingsPopUp, SIGNAL(settingsChanged(std::map<QString,QString>)),
            this, SLOT(updateButtons(std::map<QString,QString>)));
    connect(this->settingsPopUp, SIGNAL(settingsChanged(std::map<QString,QString>)),
            this, SLOT(updateLEDs(std::map<QString,QString>)));

    auto settings = Settings::readSettings(this->settingsPopUp->getPath());
    this->updateCharts(settings);
    this->updateButtons(settings);
    this->updateLEDs(settings);

    connect(ui->btn1, SIGNAL(clicked()), this, SLOT(push_cmd_1()));
    connect(ui->btn2, SIGNAL(clicked()), this, SLOT(push_cmd_2()));
    connect(ui->btn3, SIGNAL(clicked()), this, SLOT(push_cmd_3()));
    connect(ui->btn4, SIGNAL(clicked()), this, SLOT(push_cmd_4()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCharts(std::map<QString, QString> settings) {
    bool change1 = this->dchart1 == nullptr ||
            settings["URL1"].toStdString() != this->dchart1->getURL() ||
            settings["TITLE1"] != this->dchart1->getTitle() ||
            settings["POINTS1"].toInt() != this->dchart1->getNumPoints() ||
            settings["DELAY1"].toInt() != this->dchart1->getDelay() ||
            settings["BLOCKS1"].toInt() != this->dchart1->getNumBlocks();

    bool change2 = this->dchart2 == nullptr ||
            settings["URL2"].toStdString() != this->dchart2->getURL() ||
            settings["TITLE2"] != this->dchart2->getTitle() ||
            settings["POINTS2"].toInt() != this->dchart2->getNumPoints() ||
            settings["DELAY2"].toInt() != this->dchart2->getDelay() ||
            settings["BLOCKS2"].toInt() != this->dchart2->getNumBlocks();

    bool change3 = this->dchart3 == nullptr ||
            settings["URL3"].toStdString() != this->dchart3->getURL() ||
            settings["TITLE3"] != this->dchart3->getTitle() ||
            settings["POINTS3"].toInt() != this->dchart3->getNumPoints() ||
            settings["DELAY3"].toInt() != this->dchart3->getDelay() ||
            settings["BLOCKS3"].toInt() != this->dchart3->getNumBlocks();

    bool change4 = this->dchart4 == nullptr ||
            settings["URL4"].toStdString() != this->dchart4->getURL() ||
            settings["TITLE4"] != this->dchart4->getTitle() ||
            settings["POINTS4"].toInt() != this->dchart4->getNumPoints() ||
            settings["DELAY4"].toInt() != this->dchart4->getDelay() ||
            settings["BLOCKS4"].toInt() != this->dchart4->getNumBlocks();


    if (change1) {
        delete this->dchart1;

        int p = settings["POINTS1"].toInt();
        int d = settings["DELAY1"].toInt();
        int b = settings["BLOCKS1"].toInt();

        this->dchart1 = new DynChart(ui->chart1, settings["TITLE1"], settings["URL1"].toStdString(), p, d, b);
    }

    if (change2) {
        delete this->dchart2;

        int p = settings["POINTS2"].toInt();
        int d = settings["DELAY2"].toInt();
        int b = settings["BLOCKS2"].toInt();

        this->dchart2 = new DynChart(ui->chart2, settings["TITLE2"], settings["URL2"].toStdString(), p, d, b);
    }

    if (change3) {
        delete this->dchart3;

        int p = settings["POINTS3"].toInt();
        int d = settings["DELAY3"].toInt();
        int b = settings["BLOCKS3"].toInt();

        this->dchart3 = new DynChart(ui->chart3, settings["TITLE3"], settings["URL3"].toStdString(), p, d, b);
    }

    if (change4) {
        delete this->dchart4;

        int p = settings["POINTS4"].toInt();
        int d = settings["DELAY4"].toInt();
        int b = settings["BLOCKS4"].toInt();

        this->dchart4 = new DynChart(ui->chart4, settings["TITLE4"], settings["URL4"].toStdString(), p, d, b);
    }
}

void MainWindow::updateButtons(std::map<QString, QString> settings) {
    this->ui->btn1->setText(settings["BTNTITLE1"]);
    this->ui->btn2->setText(settings["BTNTITLE2"]);
    this->ui->btn3->setText(settings["BTNTITLE3"]);
    this->ui->btn4->setText(settings["BTNTITLE4"]);

    this->cmd1 = settings["BTNURL1"];
    this->cmd2 = settings["BTNURL2"];
    this->cmd3 = settings["BTNURL3"];
    this->cmd4 = settings["BTNURL4"];
}

void MainWindow::updateLEDs(std::map<QString, QString> settings) {
    bool change1 = this->led1 == nullptr || this->led1->getUrl() != settings["INDURL1"]
                || this->ui->led1_txt->text() != settings["INDTITLE1"];

    bool change2 = this->led2 == nullptr || this->led2->getUrl() != settings["INDURL2"]
                || this->ui->led2_txt->text() != settings["INDTITLE2"];

    if (change1) {
        delete this->led1;
        this->led1 = new LED(this->ui->led1, settings["INDURL1"].toStdString(), 1000);
        this->ui->led1_txt->setText(settings["INDTITLE1"]);
    }

    if (change2) {
        delete this->led2;
        this->led2 = new LED(this->ui->led2, settings["INDURL2"].toStdString(), 1000);
        this->ui->led2_txt->setText(settings["INDTITLE2"]);
    }



}


void MainWindow::showSettings() {
    this->settingsPopUp->show();
}

void MainWindow::push_cmd_1() {
    GrabApi::request(this->cmd1.toStdString());
}

void MainWindow::push_cmd_2() {
    GrabApi::request(this->cmd2.toStdString());
}

void MainWindow::push_cmd_3() {
    GrabApi::request(this->cmd3.toStdString());
}

void MainWindow::push_cmd_4() {
    GrabApi::request(this->cmd4.toStdString());
}



