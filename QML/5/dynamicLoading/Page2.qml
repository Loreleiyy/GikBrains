import QtQuick 2.15

Rectangle {
    width: parent.width
    height: parent.height - 30
    Text{
        text: "Вторая"
        color: "red"
        anchors.centerIn: parent.Center
    }
    Rectangle{
        color: "yellow"
        width: 300
        height: 100
        x: 100
        y: 100
    }
    Rectangle{
        color: "green"
        width: 150
        height: 300
        x: 600
        y: 200
    }
    Rectangle{
        color: "blue"
        width: 100
        height: 100
        x: 200
        y: 400
        radius: 100
    }
}
