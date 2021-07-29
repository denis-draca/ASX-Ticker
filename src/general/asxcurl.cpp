#include "asxcurl.h"

ASXcURL::ASXcURL(QObject *parent) : QObject(parent)
{
    m_baseURL       = QStringLiteral("https://apidojo-yahoo-finance-v1.p.rapidapi.com/market/v2/get-quotes?region=AU&symbols=");
    m_baseURLChart  = QStringLiteral("https://apidojo-yahoo-finance-v1.p.rapidapi.com/stock/v2/get-chart?interval=1d&symbol=%1&range=2y&region=AU");
    m_tickerSuffix  = QStringLiteral(".AX");
    m_comma         = QStringLiteral("%2C");
}
//
ASXcURL::~ASXcURL()
{
}

int ASXcURL::curlASX(QString &request_template, std::string &response_string)
{
    auto curl = curl_easy_init();

    QString keyString = QStringLiteral("x-rapidapi-key: %1").arg(m_apiKey);

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, request_template.toStdString().c_str());

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, keyString.toStdString().c_str());
        headers = curl_slist_append(headers, "x-rapidapi-host: apidojo-yahoo-finance-v1.p.rapidapi.com");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ASXcURL::writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        CURLcode ret = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        if(ret != CURLcode::CURLE_OK){
            return 0;
        }
        return 1;
    }

    return 0;
}

void ASXcURL::enumerateASX()
{
    QString request_template = m_baseURL;

    for(auto &ticker:m_registeredTickers){
        request_template.append(ticker).append(m_tickerSuffix).append(m_comma);
    }

    std::string response_string;

    if(curlASX(request_template, response_string)){
        emit rawResult(QString::fromStdString(response_string));

    }else {
        emit message(QStringLiteral("Error accessing ASX"));
    }

    emit updateComplete();
}

size_t ASXcURL::writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data)
{
    data->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

void ASXcURL::update()
{
    QFuture<void> future = QtConcurrent::run(this, &ASXcURL::enumerateASX);
}

void ASXcURL::registerTicker(QString &name)
{
    for(auto &ticker:m_registeredTickers){
        if(ticker.compare(name) == 0){
            return;
        }
    }

    m_registeredTickers.push_back(name);
}

void ASXcURL::getCharts()
{

}

bool ASXcURL::checkTickerValid()
{
    QString name = m_setTicker;

    QString request_template = m_baseURL;

    request_template.append(name).append(m_tickerSuffix);

    std::string response;

    if(curlASX(request_template, response)){
        size_t pos = response.find("regularMarketPrice");

        if(pos != std::string::npos){
            emit validTicker(name);
            return true;
        }else{
            emit invalidTickker();
            return false;
        }
    }

    emit invalidTickker();
    return false;
}

void ASXcURL::getTickerValue(QString rawResul)
{
    auto j = nlohmann::json::parse(rawResul.toStdString());

    QString comparison = QString("\"%1%2\"").arg(m_setTicker).arg(m_tickerSuffix);

    auto topLevel = j["quoteResponse"]["result"];

    for(auto &val:topLevel){
        if(comparison.compare(val["symbol"].dump().c_str()) == 0){
            QString valStr = val["regularMarketPrice"].dump().c_str();

            emit tickerMarketValue(valStr.toDouble());
        }
    }
}
