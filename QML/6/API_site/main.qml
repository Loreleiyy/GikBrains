import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2

import "FunctionAPI.js" as JS

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("NASA API")
    property string respon: "value"
    property string nasaAPI: "XXjr3tcE2Sk1zrHByL9jW8dCZTYHnExKPi5nM77m"  // свой api_key

    Column{
        spacing: 20

        anchors.fill: parent
        Rectangle{

            width: parent.width
            height: 40
            color: "lightgreen"

            Button {
                id: _apod
                anchors.verticalCenter: parent.verticalCenter
                text: "APOD"
                background: Rectangle{
                    color: "green"
                }
                onClicked:{JS.apod();}
            }
        }
        Rectangle{
            width: parent.width
            height: 40
            color: "lightblue"

            Button {
                id: _NeoWs
                anchors.verticalCenter: parent.verticalCenter
                text: "NeoWs"
                background: Rectangle{
                    color: "blue"
                }
                onClicked: JS.neoWs()
            }
        }

        Rectangle{
            width: parent.width
            height: 40
            color: "#ff9c00"

            Button {
                anchors.verticalCenter: parent.verticalCenter
                text: "DONKI"
                background: Rectangle{
                    color: "#ff5a00"  // оранжевый
                }
                onClicked: JS.donkiGeomagneticStorm()
            }
        }

        Rectangle{
            width: parent.width
            height: 40
            color: "#fff400"

            Button {
                anchors.verticalCenter: parent.verticalCenter
                text: "EARTH"
                background: Rectangle{
                    color: "#ff0000"
                }
                onClicked: {
                    JS.earth()
                }
            }
        }

        Rectangle{
            width: parent.width
            height: 40
            color: "#42ffe9"

            Button {
                anchors.verticalCenter: parent.verticalCenter
                text: "Fireball Data API"
                background: Rectangle{
                    color: "#30d5c8"        // Бирюзовый
                }
                onClicked: JS.fireball()
            }
        }

        Rectangle{
            width: parent.width
            height: 40
            border.width: 2
            Text{
                anchors.centerIn: parent
                text: "Gismeteo API"
                color: "red"
            }
        }

        Rectangle{
            width: parent.width
            height: 40
            color: "lightyellow"

            Button {
                anchors.verticalCenter: parent.verticalCenter
                text: "GISMeteo"
                background: Rectangle{
                    color: "yellow"
                }
                onClicked: JS.gisMeteo()
            }
        }
        Rectangle{
            width: parent.width
            height: 40
            color: "lightyellow"

            Button {
                anchors.verticalCenter: parent.verticalCenter
                text: "console"
                background: Rectangle{
                    color: "yellow"
                }
                onClicked: console.log(respon)      // для отладки
            }
        }   // Rectangle
    }       // Column
} // Window
