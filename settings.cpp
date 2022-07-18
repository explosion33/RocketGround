#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(update()));

    std::map<QString, QString> settings = Settings::readSettings();

    ui->url1->setText(settings["URL1"]);
    ui->url2->setText(settings["URL2"]);
    ui->url3->setText(settings["URL3"]);
    ui->url4->setText(settings["URL4"]);

    ui->title1->setText(settings["TITLE1"]);
    ui->title2->setText(settings["TITLE2"]);
    ui->title3->setText(settings["TITLE3"]);
    ui->title4->setText(settings["TITLE4"]);

    ui->url1_2->setText(settings["BTNURL1"]);
    ui->url2_2->setText(settings["BTNURL2"]);
    ui->url3_2->setText(settings["BTNURL3"]);
    ui->url4_2->setText(settings["BTNURL4"]);

    ui->title1_2->setText(settings["BTNTITLE1"]);
    ui->title2_2->setText(settings["BTNTITLE2"]);
    ui->title3_2->setText(settings["BTNTITLE3"]);
    ui->title4_2->setText(settings["BTNTITLE4"]);

    ui->blocks1->setValue(settings["BLOCKS1"].toInt());
    ui->blocks2->setValue(settings["BLOCKS2"].toInt());
    ui->blocks3->setValue(settings["BLOCKS3"].toInt());
    ui->blocks4->setValue(settings["BLOCKS4"].toInt());

    ui->points1->setValue(settings["POINTS1"].toInt());
    ui->points2->setValue(settings["POINTS2"].toInt());
    ui->points3->setValue(settings["POINTS3"].toInt());
    ui->points4->setValue(settings["POINTS4"].toInt());

    ui->delay1->setValue(settings["DELAY1"].toInt());
    ui->delay2->setValue(settings["DELAY2"].toInt());
    ui->delay3->setValue(settings["DELAY3"].toInt());
    ui->delay4->setValue(settings["DELAY4"].toInt());

    ui->url_led1->setText(settings["INDURL1"]);
    ui->url_led2->setText(settings["INDURL2"]);

    ui->title_led1->setText(settings["INDTITLE1"]);
    ui->title_led2->setText(settings["INDTITLE2"]);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::writeSettings(std::map<QString, QString> settings) {
    std::ofstream out("settings.ini");

    for (auto const& x : settings)
    {
        out << x.first.toStdString()  // string (key)
            << " = "
            << x.second.toStdString() // string's value
            << std::endl;
    }

    out.close();
}

void Settings::update() {
    std::map<QString, QString> settings;
    settings["URL1"] = ui->url1->text();
    settings["URL2"] = ui->url2->text();
    settings["URL3"] = ui->url3->text();
    settings["URL4"] = ui->url4->text();

    settings["TITLE1"] = ui->title1->text();
    settings["TITLE2"] = ui->title2->text();
    settings["TITLE3"] = ui->title3->text();
    settings["TITLE4"] = ui->title4->text();

    settings["BLOCKS1"] = QString::number(ui->blocks1->value());
    settings["BLOCKS2"] = QString::number(ui->blocks2->value());
    settings["BLOCKS3"] = QString::number(ui->blocks3->value());
    settings["BLOCKS4"] = QString::number(ui->blocks4->value());

    settings["POINTS1"] = QString::number(ui->points1->value());
    settings["POINTS2"] = QString::number(ui->points2->value());
    settings["POINTS3"] = QString::number(ui->points3->value());
    settings["POINTS4"] = QString::number(ui->points4->value());

    settings["DELAY1"] = QString::number(ui->delay1->value());
    settings["DELAY2"] = QString::number(ui->delay2->value());
    settings["DELAY3"] = QString::number(ui->delay3->value());
    settings["DELAY4"] = QString::number(ui->delay4->value());


    settings["BTNURL1"] = ui->url1_2->text();
    settings["BTNURL2"] = ui->url2_2->text();
    settings["BTNURL3"] = ui->url3_2->text();
    settings["BTNURL4"] = ui->url4_2->text();

    settings["BTNTITLE1"] = ui->title1_2->text();
    settings["BTNTITLE2"] = ui->title2_2->text();
    settings["BTNTITLE3"] = ui->title3_2->text();
    settings["BTNTITLE4"] = ui->title4_2->text();

    settings["INDURL1"] = ui->url_led1->text();
    settings["INDURL2"] = ui->url_led2->text();

    settings["INDTITLE1"] = ui->title_led1->text();
    settings["INDTITLE2"] = ui->title_led2->text();



    emit settingsChanged(settings);
    this->writeSettings(settings);
    this->close();
}

std::map<QString, QString> Settings::readSettings() {
    std::map<QString, QString> settings;

    std::ifstream in("settings.ini");
    std::string line;
    while (std::getline (in, line)) {
        int s = line.find(" = ");
        std::string key = line.substr(0, s);
        std::string val = line.substr(s+3);

        settings[QString::fromStdString(key)] = QString::fromStdString(val);
    }

    return settings;
}
