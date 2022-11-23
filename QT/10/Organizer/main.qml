import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Organizer 1.0


Window {
    id: _wind
    width: 800
    height: 600
    visible: true
    title: qsTr("Organizer")

    Rectangle{
        y: 100
        x: 100
        border.width: 2
        border.color: "black"
        width: 150
        height: 30
        TextInput{
            id: _name
            anchors.centerIn: parent
            text: "Name"
            selectionColor: "black"
            width: 100
        }
        Text{
            text: "Name"
            anchors.bottom: parent.top
            color: "red"
        }
    }
    Rectangle{
        y: 150
        x: 100
        border.width: 2
        border.color: "black"
        width: 150
        height: 30
        TextInput{
            id: _date
            width: 100

            text: "20.11.2022"
            anchors.centerIn: parent
        }
        Text{
            text: "Date  dd.MM.yyyy"
            anchors.bottom: parent.top
            color: "red"
        }
    }
    Rectangle{
        y: 200
        x: 100
        border.width: 2
        border.color: "black"
        width: 150
        height: 30
        TextInput{
            id: _progress
            width: 100

            text: "5"
            anchors.centerIn: parent

        }
        Text{
            text: "Progress"
            anchors.bottom: parent.top
            color: "red"
        }
    }


        NewButton{
            x: 400
            y: 150
            width: 100
            height: 30
            text: "Save task"
            onClicked: {_organizer.setTask(_name.text.toString(), _date.text.toString(), _progress.text.toString())                       }
        }
        Organizer{
            id: _organizer
        }

}
