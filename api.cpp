#include "api.h"

Api::Api() {
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(recieved(QNetworkReply*)));


}

Api::~Api() {

}

void Api::request(QString url) {
    manager->get(QNetworkRequest(QUrl(url)));
}

void Api::recieved(QNetworkReply *reply) {
    qDebug() << reply->error();
}
