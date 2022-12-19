import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "Loading.js" as LoadingJS

Window {
    id: root
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")
    color: "#e5ecef"

    LoadingPage{
        id: _page0
        onVisibleChanged: {             // при удалении LoadingPage
            LoadingJS.createPage1(root)
            _next.visible = true
        }

    }

    Loader{
        id: _load
    }

    Button{
        id: _prev
        width: 150
        height: 30
        visible: false
        anchors.bottom: parent.bottom
        text: "Предыдущая"
        onClicked: {
            _prev.visible = false
            _next.visible = true
            LoadingJS.deletePage2()
            LoadingJS.createPage1(root)
        }
    }

    Button{
        id: _next
        width: 150
        height: 30
        visible: false
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        text: "Следующая"
        onClicked: {
            _next.visible = false
            _prev.visible = true
            LoadingJS.deletePage1()
            LoadingJS.createPage2(root)
        }
    }
}
