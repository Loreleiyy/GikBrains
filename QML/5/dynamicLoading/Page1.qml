import QtQuick 2.15

Rectangle {
    width: parent.width
    height: parent.height - 30
    Text{
        text: "Первая"
        color: "blue"
        anchors.centerIn: parent.centerIn
    }

    Rectangle{              // какее то фигуры
        color: "red"
        width: 300
        height: 100
        x: 50
        y: 50
    }
    Rectangle{
        color: "green"
        width: 150
        height: 150
        x: 450
        y: 400
    }
    Rectangle{
        color: "blue"
        width: 200
        height: 200
        x: 250
        y: 250
        radius: 100
    }
}
