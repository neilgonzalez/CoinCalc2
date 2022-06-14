import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.12
import io.qt.examples.backend 1.0

ApplicationWindow {
    width: 300
    height: 400
    visible: true
    Material.theme: Material.Dark
    Material.accent: Material.Purple

    title: qsTr("Coin Converter")

    BackEnd {
           id: backend
       }
    Column{
        anchors.centerIn: parent

        TextField {
            text: backend.userName
            placeholderText: qsTr("Enter you amount (Ex: 0.000234)")
            width: 200

            onEditingFinished: backend.userName = text

        }

        ComboBox {
            id: typeComboBox
            width: 200
            model: ListModel {
                   id: cbItems
                   ListElement { text: "BTC" }
                   ListElement { text: "ETH" }
                   ListElement { text: "XMR" }
                   ListElement { text: "LTC" }
                   ListElement { text: "XRP" }

               }
            textRole: "text"
             onCurrentIndexChanged: backend.setComboCoinFrom(cbItems.get(currentIndex).text)
        }
        Label {
            text: "Convert to"
        }
        ComboBox {
            width: 200
            id: typeComboBox2

            model: ListModel {
                   id: cbItems2
                   ListElement { text: "BTC" }
                   ListElement { text: "ETH" }
                   ListElement { text: "XMR" }
                   ListElement { text: "LTC" }
                   ListElement { text: "XRP" }

               }
            textRole: "text"
             onCurrentIndexChanged: backend.setComboCoinTo(cbItems2.get(currentIndex).text)
        }



        Button {
            text: "Ok"
            //used for displaying the desired output
            onClicked: backend.calculate(backend.userName)
        }


    }


}
