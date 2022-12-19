import QtQuick 2.15
import QtQuick.Controls 2.15            // взял из 1 урока

Rectangle {
    id: secondaryFrame
    color: "white"
    anchors.centerIn: parent
    radius: 5
    width: 300
    height: 250
    property string textColor: "#535353"
    property string login: "login"
    property string pasword: "pasword"

    Column {
        anchors.fill: parent
        padding: 32
        spacing: 32
        TextField {
            id: loginTextField
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: qsTr("Логин")
            color: secondaryFrame.textColor
        }
        TextField {
            id: passwordTextField
            echoMode: TextInput.Password
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: qsTr("Пароль")
            color: secondaryFrame.textColor
        }
        Button {
            id: submitButton
            width: 200
            height: 40
            background: Rectangle {
                color: parent.down ? "#bbbbbb" : (parent.hovered ? "#d6d6d6" : "#f6f6f6")
            }
            text: qsTr("Вход")
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                if(loginTextField.text == login && passwordTextField.text == pasword){
                    successAnimation.start()
                }
                else{
                    failAnimation.start()
                }
            }
        }
    }


    ParallelAnimation{
        id: failAnimation
        SequentialAnimation {

            PropertyAnimation {

                targets: [loginTextField, passwordTextField]
                property: "color"
                to: "dark red"
                duration: 0
            }
            PropertyAnimation {

                targets: [loginTextField, passwordTextField]
                property: "color"
                to: secondaryFrame.textColor
                duration: 400
            }
        }
        SequentialAnimation {

            NumberAnimation { target: secondaryFrame; property:
                    "anchors.horizontalCenterOffset"; to: -5; duration: 50 }
            NumberAnimation { target: secondaryFrame; property:
                    "anchors.horizontalCenterOffset"; to: 5; duration: 100 }
            NumberAnimation { target: secondaryFrame; property:
                    "anchors.horizontalCenterOffset"; to: 0; duration: 50 }
        }
    }

    SequentialAnimation{
        id: successAnimation
        PropertyAnimation {
            targets: [loginTextField, passwordTextField, submitButton]
            property: "opacity"
            to: 0
            duration: 400
        }
        PropertyAnimation {
            target: secondaryFrame
            property: "opacity"
            to: 0
            duration: 600
        }
        onFinished: {
            visible = false
            secondaryFrame.destroy()
        }

    }

}
