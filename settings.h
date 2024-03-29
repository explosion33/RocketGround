#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QDebug>
#include <map>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>

#include <fstream>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    static std::map<QString, QString> readSettings(std::string path);
    std::string getPath();

signals:
    void settingsChanged(std::map<QString, QString> settings);

private:
    Ui::Settings *ui;
    void writeSettings(std::map<QString, QString> settings);
    void writeDefaults();
    std::string settingsPath;

private slots:
    void update();
};

#endif // SETTINGS_H
