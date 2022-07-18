#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QRandomGenerator>
#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>

#include <map>

#include "dynchart.h"
#include "led.h"
#include "grabapi.h"
#include "settings.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showSettings();
    void updateCharts(std::map<QString, QString> settings);
    void updateButtons(std::map<QString, QString> settings);
    void updateLEDs(std::map<QString, QString> settings);

    void push_cmd_1();
    void push_cmd_2();
    void push_cmd_3();
    void push_cmd_4();

private:
    Ui::MainWindow *ui;

    Settings *settingsPopUp;

    DynChart *dchart1;
    DynChart *dchart2;
    DynChart *dchart3;
    DynChart *dchart4;

    LED *led1;
    LED *led2;

    QString cmd1;
    QString cmd2;
    QString cmd3;
    QString cmd4;


signals:
    void startObj();

};
#endif // MAINWINDOW_H
