#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <string>
#include <iostream>
#include <QDebug>


class util {

public:
    util();
    QString SanitizeResponse(QString& coin);
    double StrToDouble(QString& coin);
    double ConvertCoins(double coin1, double coin2, QString& amount);

};

#endif // UTIL_H
