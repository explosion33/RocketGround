#ifndef API_H
#define API_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

class Api : public QObject
{
    Q_OBJECT

public:
    Api();
    ~Api();

    void request(QString url);

private:
    QNetworkAccessManager *manager;



signals:


private slots:
    void recieved(QNetworkReply *reply);


};

#endif // API_H
