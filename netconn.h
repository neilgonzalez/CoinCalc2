#ifndef NETCONN_H
#define NETCONN_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QApplication>


class netconn : public QObject
{
public:
    netconn();
    void TestConnection(QString& coin, QString& amount);
    virtual ~netconn() {};
    QString GetExchangeRate(const QString& coin);
    QString GetResponse() const;
    QString GetConversion() const;
    bool GetRecieved() const;
    void SetFlagToFalse();
private:
    QNetworkAccessManager* manager;
    QString response;
    QString conversion;
    bool recievedResponse;

};

#endif // NETCONN_H
