#include "netconn.h"
#include <string>
#include <QNetworkRequest>
#include <vector>

netconn::netconn() {
    manager = new QNetworkAccessManager();
    recievedResponse = false;
}

//API to get coin exchagne rate in USD
QString netconn::GetExchangeRate(const QString& coin){
    int j = 0;
    std::vector<std::string> myvector;
    std::string value  = "";
    while ((j = response.indexOf(coin, j)) != -1) {
        for(int i = 5; i < 22; i++) {
            value = value + response[j + i].toLatin1();
        }
        if (value.find("USD") != std::string::npos){
            //std::cout << value << std::endl;
            myvector.push_back(value);
        }

        //lambda expression to find a substring of USD
        if(std::find_if(myvector.begin(), myvector.end(),
                        []( const std::string& str) {
                            return str.find("USD") != std::string::npos; }) != myvector.end()) {
                            conversion =  QString::fromStdString(myvector.back());
        }
        ++j;
        value = "";
    }
    return conversion;
}


QString netconn::GetResponse() const {return response; }
bool netconn::GetRecieved() const { return recievedResponse; }

QString netconn::GetConversion() const {
    return conversion;
}

void netconn::SetFlagToFalse() {
    recievedResponse = false;
}


void netconn::TestConnection(QString& coin, QString& amount){
    std::string urlString = "https://exchangerate.guru/" + coin.toStdString() + "/usd/" + amount.toStdString();
    QString newUrl = QString::fromStdString(urlString);
    qDebug() << "FETCHING: " << newUrl;
    QNetworkRequest request;
    request.setUrl(QUrl(newUrl));
    manager->get(request);
    connect(manager, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
               if (reply->error()) {
                   qDebug() << reply->errorString();
                   return;
               }
               QString answer = reply->readAll();
               response = answer;
               QString ExchangeCoin = GetExchangeRate(coin);
               conversion = ExchangeCoin;
               //waits until network request is complete
               // GetConversion();
               recievedResponse = true;

            //    qDebug() << conversion ;
           }
       );

}

