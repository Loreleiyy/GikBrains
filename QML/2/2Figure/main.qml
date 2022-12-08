import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    property bool isRect: true
    Rectangle{
        id: _rect
        width: 300
        height: 300
        color: "black"
        anchors.centerIn: parent
        transform: Rotation{
            id: _rotat
            origin.x: 150
            origin.y: 150
            angle: 0
        }
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onClicked: (mouse)=>{
                       if(mouse.button === Qt.LeftButton){
                           parent.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
                           }
                           else{
                               _anim.running = true}
                       }
            onDoubleClicked: {if(isRect) parent.radius = 150
                else parent.radius = 0
                isRect = !isRect
            }
        }
    }
    PropertyAnimation{
        id: _anim
        target: _rotat
        property: "angle"
        duration: 5000
        from: 0
        to: 360

    }
}
