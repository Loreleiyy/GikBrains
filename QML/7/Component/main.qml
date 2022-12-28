import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

// Task 7.3 QML

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")
    CustomPopup{
        id: _popup
        width: 100
        height: 100
        x: 300
        y: 300
        modal: true


        Text{
            anchors.centerIn: parent.Center
            text: "Popup open"
        }

    }

    Button{
        anchors.bottom: parent.bottom
        width: 150
        height: 30
        text: "Custom Popup"
        onClicked: {
            _popup.open()
        }
        onReleased: {
            _popup.close()
        }
    }

    CustomComboBox{
        id: _box
        width: 150
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        model: ["one", "two", "three", "four"]
    }
}
