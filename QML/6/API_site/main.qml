import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2

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
                onClicked:{apod()}
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
                onClicked: neoWs()
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
                onClicked: donkiGeomagneticStorm()
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
                    earth()
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
                onClicked: fireball()
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
                onClicked: gisMeteo()
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

    function uhttp(url){
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function(){
            if(xmlhttp.readyState == XMLHttpRequest.DONE && xmlhttp.status == 200) {
                //respon = xmlhttp.responseText.toString()
                //jsonParse(xmlhttp.responseText)
                console.log(xmlhttp.responseText)
            }

        }
        xmlhttp.open("GET", url, false)
        xmlhttp.send()
        return xmlhttp.responseText;
    }

    function apod(){
        console.log("apod");
        var url = "https://api.nasa.gov/planetary/apod?api_key=" + nasaAPI;
        var obj = uhttp(url);
        jsonParse(obj);
    }

    function neoWs(){
        console.log("NeoWs");
        var url = "https://api.nasa.gov/neo/rest/v1/feed?start_date=2022-12-15&end_date=2022-12-16&api_key=" + nasaAPI;
        uhttp(url);
    }

    function donkiGeomagneticStorm(){
        console.log("DONKI");
        var url = "https://api.nasa.gov/DONKI/FLR?start_date=2022-12-15&end_date=2022-12-16&api_key=" + nasaAPI;
        uhttp(url);
    }

    function earth(){
        console.log("EARTH");
        var url = "https://api.nasa.gov/planetary/earth/assets?lon=83.10&lat=54.75&date=2021-11-16&&dim=0.10&api_key=" + nasaAPI;
        uhttp(url);
    }

    function fireball(){
        console.log("Fireball Data API");
        var url = "https://ssd-api.jpl.nasa.gov/fireball.api?limit=3";
        uhttp(url)
    }

    function gisMeteo(){
        console.log("gis()");
        var xmlhttp = new XMLHttpRequest();
        var url = "https://api.gismeteo.net/v2/search/cities/?latitude=54.75&longitude=83.10&limit=10";
        xmlhttp.onreadystatechange = function(){
            if(xmlhttp.readyState == XMLHttpRequest.DONE && xmlhttp.status == 200) {
                console.log("успех gis")
            }
            console.log(xmlhttp.responseText)
        }

        xmlhttp.open("GET", url)

        xmlhttp.setRequestHeader('X-Gismeteo-Token', '56b30cb255.3443075');       // Invalid token получить новый проблематично
        xmlhttp.setRequestHeader('Content-type','application/json; charset=utf-8');
        xmlhttp.send()
    }

    function jsonParse(response){
        var jsonObj = JSON.parse(response)
        var img = jsonObj.url;
        console.log("jsonParse");
        console.log(img);
        respon = img;
    }

} // Window
