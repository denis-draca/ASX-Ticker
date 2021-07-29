#ifndef ASXCURL_H
#define ASXCURL_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include <QThreadPool>

#include <curl/curl.h>

#include <vector>

#include <nlohmann/json.hpp>

#include <iostream>

class ASXcURL : public QObject
{
    Q_OBJECT
public:
    explicit ASXcURL(QObject *parent = nullptr);
    ~ASXcURL();

signals:
    void validTicker(QString name);
    void invalidTickker();
    void rawResult(QString res);
    void tickerMarketValue(double val);
    void message(QString msg);
    void updateComplete();

public slots:
    bool checkTickerValid();
    void getTickerValue(QString rawResul);
    void setApiKey(QString key){m_apiKey = key;}

private:
    int curlASX(QString &request_template, std::string &response_string);
    void enumerateASX();

    static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);

private:
    QString m_baseURL;
    QString m_baseURLChart;
    QString m_comma;
    QString m_tickerSuffix;
    QString m_setTicker;
    QString m_apiKey;

    std::vector<QString> m_registeredTickers;

public:
    void setTicker(QString &ticker){m_setTicker = ticker;}
    void update();
    void registerTicker(QString &name);
    void getCharts();

    QString getApiKey(){return m_apiKey;}

};

#endif // ASXCURL_H
