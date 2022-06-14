#include "util.h"
#include <string>

util::util() {

}

QString util::SanitizeResponse(QString& coin) {
        std::string parseText = coin.toStdString();
        int m1 = parseText.find_first_not_of(" ");
        std::string second = parseText.substr(m1, parseText.length() - 1);
        int m2 = second.find_first_of(" ");
        std::string third = second.substr(0, m2);
        int m3 = third.find_first_of(",");
        if (m3 != std::string::npos) {
            std::string fourth = third.erase(m3, 1);
            QString output = QString::fromStdString(fourth);

            qDebug() << "[x]: " << output;
            return output;
        }

        QString output = QString::fromStdString(third);


        return output;


}

//prob
double util::StrToDouble(QString& coin) {
        std::string convert = coin.toStdString();
        std::string::size_type sz;

        double s1 = std::stod(convert, &sz);
        return s1;
}


//takes both coins in USD and converts coinFrom to coinTo
double util::ConvertCoins(double coinFrom, double coinTo, QString& amount) {
    std::string::size_type sz;
    std::string calculate = amount.toStdString();
    double inputDouble = std::stod(calculate, &sz);
    return coinFrom / coinTo * inputDouble;
}
