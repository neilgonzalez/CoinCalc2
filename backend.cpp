#include "backend.h"
#include "netconn.h"
#include "util.h"
#include <QString>
#include <QMessageBox>

//maximum wait time before continuing main thread
void wait() {
    QTime dieTime= QTime::currentTime().addSecs(3);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 3000);
}

BackEnd::BackEnd(QObject *parent) :
    QObject(parent) {

}

void BackEnd::printUser(){
        qDebug() << m_userName;
}

QString BackEnd::userName() const{

    return m_userName;

}

void BackEnd::setUserName(const QString& username) {
    if(username == m_userName) {
        return;
    }
    m_userName = username;
    emit userNameChanged();
}

Q_INVOKABLE void BackEnd::setComboCoinFrom(const QString& coin) {
    if(coin == m_comboCoinFrom) {
        return;
    }
    m_comboCoinFrom = coin;
}

Q_INVOKABLE void BackEnd::setComboCoinTo(const QString& coin) {
    if(coin == m_comboCoinTo) {
        return;
    }
    m_comboCoinTo = coin;
}




Q_INVOKABLE void BackEnd::printCoin() {
    qDebug() << "amount: " << m_userName;
    qDebug() << "convert from: " << m_comboCoinFrom;
    qDebug() << "convert to: " << m_comboCoinTo;
}

Q_INVOKABLE void BackEnd::calculate(QString& amount) {
    netconn n;
    netconn x;
    util MyUtility;
    QString myCoin1 = m_comboCoinFrom;

   n.TestConnection(myCoin1, amount);
   //once we get a response, do the conversion
   wait();

   QString xrp =   n.GetConversion();
   QString xrpString = MyUtility.SanitizeResponse(xrp);
 //  qDebug() <<  amount << " XRP: " << xrpString;

   QString myCoin2 = m_comboCoinTo;
   x.TestConnection(myCoin2, amount);
   wait();

   QString ltc = x.GetConversion();
   QString ltcString = MyUtility.SanitizeResponse(ltc);

   double coin1 = MyUtility.StrToDouble(xrpString);
   double coin2 = MyUtility.StrToDouble(ltcString);
   double result = MyUtility.ConvertCoins(coin1, coin2, amount);

   qDebug() << "conversion from " << amount << myCoin1 << " to " << amount <<  " " << myCoin2 << " :" << result;

    std::string finalConv = std::to_string(result);
    QString finalStr = QString::fromStdString(finalConv);
    QMessageBox msgBox;
    msgBox.setText(finalStr);
    msgBox.exec();


}
