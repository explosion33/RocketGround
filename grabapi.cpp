#include "grabapi.h"

GrabApi::GrabApi(std::string url, int delay, bool rolling, int numPoints) {
    this->url = url;
    this->delay = delay;
    this->size = 0;
    this->rolling = rolling;
    this->numPoints = numPoints;
}

void GrabApi::timerEvent(QTimerEvent *event) {
    std::string res;
    if (this->rolling) {
        res = GrabApi::request(this->url + "/" + std::to_string(1 + (this->numPoints * -1)));
    }
    else {
        res = GrabApi::request(this->url + "/" + std::to_string(this->size));
    }

    if (res != "") {
        std::vector<std::vector<double>> list = this->parseList(res);

        if (rolling) {
            emit appendPoints(list);
        }
        else {
            for (auto point : list) {
                emit addPoint(point[0], point[1]);
            }
        }
    }
}

void GrabApi::start() {
    this->timerId = startTimer(delay);
}

void GrabApi::stop() {
    killTimer(timerId);
    timerId = 0;
}

void GrabApi::Delete() {
    delete this;
}

size_t GrabApi::curlWriteCallback(void* contents, size_t size, size_t nmemb, std::string* s)
{
    size_t newLength = size * nmemb;
    try
    {
        s->append((char*)contents, newLength);
    }
    catch (std::bad_alloc& e)
    {
        //handle memory problem
        return 0;
    }
    return newLength;
}

std::string GrabApi::request(std::string url) {
    CURL* curl;
    CURLcode code;
    std::string res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GrabApi::curlWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        code = curl_easy_perform(curl);
        /* Check for errors */
        if (code != CURLE_OK) {
            //qDebug() << "Error " << code;
            curl_easy_cleanup(curl);
            return "";
        }

        /* always cleanup */
        curl_easy_cleanup(curl);

    }
    return res;
}

GrabApi::~GrabApi() {}

std::vector<std::vector<double>> GrabApi::parseList(std::string data) {
    std::vector<std::vector<double>> out;

    std::vector<double>* point = new std::vector<double>;
    std::string currVal = "";

    for (int i = 1; i < data.length()-1; i++) {
        char c = data[i];

        if (c == '[') {
            delete point;
            point = new std::vector<double>;
        }
        else if (c == ']' || c==',') {
            if (currVal != "") {
                try {
                    point->push_back(stod(currVal));
                    currVal = "";
                }
                catch (std::invalid_argument) {
                    return *(new std::vector<std::vector<double>>);
                }
            }
            if (c == ']') {
                if (point->size() > 0) {
                    out.push_back(*point);
                }
            }
        }
        else if (c != ',') {
            currVal += c;
        }

    }
    delete point;
    return out;
}
