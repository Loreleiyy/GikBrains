import QtQuick 2.15

BorderImage {
    signal clicked
    property alias text: _txt.text
    source: "qrc:///img/Button1.png"
    width: _txt.width + 15
    height: _txt.height + 15

    Text{
        id: _txt
        anchors.centerIn: parent
    }
    MouseArea{
        anchors.fill: parent
        onClicked: parent.clicked()
        onPressed: {parent.source = "qrc:///img/Button2.png"}
        onReleased: {parent.source = "qrc:///img/Button1.png"}
    }

}
