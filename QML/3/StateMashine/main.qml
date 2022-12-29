import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Состояние программы")
    color: "#e5ecef"

    property string login: "login"
    property string pasword: "pasword"

    Rectangle{
        id: _secondaryFrame
        color: "white"
        anchors.centerIn: parent
        width: 300
        height: 250
        radius: 5
        visible: true
        property string textColor: "#535353"
        state: "user is not logged"

        Column{
            anchors.fill: parent
            spacing: 30
            padding: 30
            TextField {
                id: loginTextField
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: qsTr("Логин")
                color: _secondaryFrame.textColor
            }
            TextField {
                id: passwordTextField
                echoMode: TextInput.Password
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: qsTr("Пароль")
                color: _secondaryFrame.textColor
            }
            Button {
                id: submitButton
                width: 200
                height: 40
                background: Rectangle {
                    color: parent.down ? "#bbbbbb" :
                               (parent.hovered ? "#d6d6d6" : "#f6f6f6")}
                text: qsTr("Вход")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if(loginTextField.text == login && passwordTextField.text == pasword){
                        _greenText.state = "user is logged"
                    }
                    else{
                        _greenText.state = "user is not logged"
                    }
                }
            }
        } // Column
    } // Rectangle

    Rectangle{
        id: _greenText
        anchors.centerIn: parent
        width: 150
        height: 150
        color: "green"
        visible: false
        Text{
            id: _text
            text: "Вы вошли в систему"
            anchors.centerIn: parent
        }
        state: "user is not logged"
        states: [
            State{
                name: "user is not logged"
                PropertyChanges{target: _secondaryFrame; visible: true;}
                PropertyChanges{target: _greenText; visible: false}
                PropertyChanges{target: _search; visible: false}
                PropertyChanges{target: _searchIndicator; visible: false}
            },
            State{
                name: "user is logged"
                PropertyChanges{target: _secondaryFrame; visible: false}
                PropertyChanges{target: _greenText; visible: true}
                PropertyChanges{target: _search; visible: true}
                PropertyChanges{target: _searchIndicator; visible: false}
            },
            State{
                name: "search"
                PropertyChanges{target: _secondaryFrame; visible: false}
                PropertyChanges{target: _text; text: "Поиск"}
                PropertyChanges{target: _searchIndicator; visible: true}
            },
            State{
                name: "search completed"
                PropertyChanges{target: _secondaryFrame; visible: false}
                PropertyChanges{target: _greenText; visible: true; color: "red"}
                PropertyChanges{target: _searchIndicator; visible: false}
                PropertyChanges{target: _text; text: "Поиск завершён"}
            }

        ]
        transitions: [
            Transition{
                from: "user is not logged"
                to: "user is logged"
                PropertyAnimation {

                    targets: [_greenText, _search]
                    property: "opacity"
                    from: 0
                    to: 1
                    duration: 500
                }
                PropertyAnimation {
                    target: _secondaryFrame
                    property: "opacity"
                    from: 1
                    to: 0
                    duration: 500
                }
            },
            Transition{
                from: "user is logged"
                to: "search"
                PropertyAnimation {
                    targets: [_greenText, _search]
                    property: "opacity"
                    from: 1
                    to: 0
                    duration: 500
                }
            },
            Transition{
                from: "search"
                to: "search completed"
                PropertyAnimation {

                    targets: [_greenText, _search]
                    property: "opacity"
                    from: 0
                    to: 1
                    duration: 500
                }
                ColorAnimation { target: _greenText; duration: 500}
            }
        ]
    }

    Button{
        id: _search
        width: 150
        height: 30
        anchors.bottom: parent.bottom
        state: "user is not logged"
        text: "Поиск"
        onClicked: {

             _greenText.state = "search"
            _timer.start()
        }
    }

    Timer{
        id: _timer
        interval: 3000
        onTriggered: {
            _greenText.state = "search completed"
        }
    }

    BusyIndicator{
        id: _searchIndicator
        anchors.horizontalCenter: parent.horizontalCenter
        state: "user is logged"
    }
}
