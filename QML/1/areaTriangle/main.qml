import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: w
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property int wid: 50
    property int hei: 20
    Column {
        x: 70
        y: 50

        padding: 32 // отступы по 4 сторонам от родительского элемента
        spacing: 32
        Rectangle{
            border.color: "black"
            width: wid
            height: hei
            TextInput{
                id: _a
                anchors.centerIn: parent
                width: 10
                text: "a"

            }
        }
        Rectangle{
            width: wid
            height: hei
            border.color: "black"
            TextInput{
                id: _b
                anchors.centerIn: parent
                width: 10
                text: "b"
            }
        }
        Rectangle{
            width: wid
            height: hei
            border.color: "black"
            TextInput{
                id: _c
                anchors.centerIn: parent
                width: 10
                text: "c"
            }
        }
    }
    Button{
        x: 200
        y: 100
        text: "Площадь по сторонам"
        onClicked: trLen()
    }
    Button{
        x: 200
        y: 200
        text: "Площадь по координатам"
        onClicked:  trCoord()


        // Данные для тестов:
        // A(0, 2), B(-1, 0), C(0, 5) → S = 6    false, erroneous coordinates

    }

    Rectangle{          // точка А
        x: 150
        y: 300
        width: 100
        height: hei
        border.color: "black"
        Rectangle{
            width: wid
            height: hei
            anchors.left: parent.left
            border.color: "black"
            TextInput{
                id: _ax
                anchors.centerIn: parent
                text: "AX"
                width: 20
            }
        }
        Rectangle{
            width: wid
            height: hei
            anchors.right: parent.right
            border.color: "black"
            TextInput{
                id: _ay
                anchors.centerIn: parent

                text: "AY"
                width: 20
            }
        }
    }

    Rectangle{          // точка В
        x: 300
        y: 300
        width: 100
        height: hei
        border.color: "black"
        Rectangle{
            width: wid
            height: hei
            anchors.left: parent.left
            border.color: "black"
            TextInput{
                id: _bx
                anchors.centerIn: parent
                text: "BX"
                width: 20
            }
        }
        Rectangle{
            width: wid
            height: hei
            anchors.right: parent.right
            border.color: "black"
            TextInput{
                id: _by
                anchors.centerIn: parent

                text: "BY"
                width: 20
            }
        }
    }

    Rectangle{              // точка С
        x: 150
        y: 350
        width: 100
        height: hei
        border.color: "black"
        Rectangle{
            width: wid
            height: hei
            anchors.left: parent.left
            border.color: "black"
            TextInput{
                id: _cx
                anchors.centerIn: parent
                text: "CX"
                width: 20
            }
        }
        Rectangle{
            width: wid
            height: hei
            anchors.right: parent.right
            border.color: "black"
            TextInput{
                id: _cy
                anchors.centerIn: parent

                text: "CY"
                width: 20
            }
        }
    }



    function trLen(){
        var a = parseFloat(_a.text)
        var b = parseFloat(_b.text)
        var c = parseFloat(_c.text)
        areaTr(a, b, c)
    }

    function lineLen(ax, ay, bx, by){
        var dx = ax - bx
        var dy = ay - by
        var dc = Math.sqrt(dx*dx + dy*dy)
        console.log(dc)
        return dc
    }

    function trCoord(){
        var ax = parseInt(_ax.text)
        var ay = parseInt(_ay.text)
        var bx = parseInt(_bx.text)
        var by = parseInt(_by.text)
        var cx = parseInt(_cx.text)
        var cy = parseInt(_cy.text)

        var a = lineLen(ax, ay, bx, by)
        var b = lineLen(ax, ay, cx, cy)
        var c = lineLen(bx, by, cx, cy)
        areaTr(a, b, c)
    }

    function areaTr( a,  b, c){

        var p = (a + b + c)/2
        console.log(p)
        var S = Math.sqrt (p*(p-a)*(p-b)*(p-c))
        console.log(S)

    }

}
