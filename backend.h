#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>
#include <QGuiApplication>
#include <QString>

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)

public:

    BackEnd(QString& text);

    explicit BackEnd(QObject *parent = nullptr);

    QString userName() const;

    void setUserName(const QString &userName);


     Q_INVOKABLE void setComboCoinFrom(const QString &coin);
     Q_INVOKABLE void setComboCoinTo(const QString &coin);
     Q_INVOKABLE void printCoin();

    Q_INVOKABLE void printUser();

    Q_INVOKABLE QString getUserName() {
        return m_userName;
    }


    //master function
    Q_INVOKABLE void calculate(QString& amount);


signals:
    void userNameChanged();


private:
    QString m_userName;
    QString m_comboCoinFrom;
    QString m_comboCoinTo;
    double result;

};

#endif // BACKEND_H
