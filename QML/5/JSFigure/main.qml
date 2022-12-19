import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "Figure.js" as Fig

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")

    ComboBox{
        id: _box
        width: 150
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        model: ["asterisk", "ring", "house", "hourglass"]
        onActivated: {
            _canvas.requestPaint()
        }
    }


    Canvas{
        id: _canvas
        anchors.fill: parent
        property int xStep: width / 2
        property int yStep: height / 2
        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            ctx.fillStyle = "blue";
            ctx.beginPath()
            var coord = Fig.figure(_box.currentValue)
            if(_box.currentValue === "ring"){
                ctx.lineCap = "round"
                ctx.arc(30*(coord[0]) + xStep, (30*(coord[1])) + yStep,
                        coord[2], coord[3], coord[4]);
            }
            else{

                for(var i = 0; i < coord.length; ++i){
                    ctx.lineTo(30*(coord[i][0]) + xStep, (30*(coord[i][1])) + yStep)
                }
                console.log(coord)
                console.log(coord.length)
                console.log(coord[0][1])
                ctx.lineCap = "square"

            }
            ctx.closePath()
            ctx.lineWidth = 3
            ctx.stroke();
            ctx.fill()

        }
    }

}
