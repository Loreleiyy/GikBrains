import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.LocalStorage 2.15

import "DBFunctions.js" as DBFunctions

// Task 7.1 QML

Window {
    id: root
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")


    Component{
        id: comp1

        DataBase1{
            id: _dataB1
            width: root.width
            height: root.height
        }
    }


    Component{
        id: comp2
        DataBase2{
            id: _dataB2
//            anchors.fill: root
            width: root.width
            height: root.height
        }
    }

    Loader{
        id: _loader
    }

    ComboBox{
        id: _box
        width: 150
        height: 30
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        model: ["DataBase1", "DataBase2"]
        onActivated: {
            if(_box.currentValue == "DataBase1"){
                _loader.sourceComponent = comp1
            }else if(_box.currentValue == "DataBase2"){
                _loader.sourceComponent = comp2
            }
        }
    }
    Component.onCompleted: {
        _loader.sourceComponent = comp1
    }

}
