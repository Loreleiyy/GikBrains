import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.LocalStorage 2.15

// Task 7.2 QML

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Data base")

    SwipeView{
        id: _swipe
        anchors.fill: parent
        currentIndex: 0
        ListView{

            model: mdl
            spacing: 2

            delegate: Row{
                width: parent.width
                height: 50
                spacing: 2
                Rectangle{
                    width: 70
                    height: parent.height
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        text: rowId
                    }
                }
                Rectangle{
                    width: 100
                    height: parent.height
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        text: name
                    }
                }
                Rectangle{
                    width: 100
                    height: parent.height
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        text: surname
                    }
                }

            } // delegate Row
            header: Row{
                width: parent.width
                height: 50
                spacing: 2

                Rectangle{
                    width: 70
                    height: parent.height
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        text: "RowId"
                    }
                }
                Rectangle{
                    width: 100
                    height: parent.height
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        text: "name"
                    }
                }
                Rectangle{
                    width: 100
                    height: parent.height
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        text: "surname"
                    }
                }
            } // header: Row

            //    Component.onCompleted: {
            //        var db = LocalStorage.openDatabaseSync("DBExample", "1.0", "Пример локальной базы данных",
            //                                               1000)
            //        try {
            //            db.transaction(DbFunctions.createSimpleTable);
            //            db.transaction((tx) => {
            //                               DbFunctions.addContact(tx, "Иванов", "Иван", "ivanoviv2182@mail.ru",
            //                                                      "+7(988)37333112")
            //                               DbFunctions.addContact(tx, "Заварнов", "Владимир", "zavlad@mail.ru",
            //                                                      "+7(977)98373331")
            //                               DbFunctions.addContact(tx, "Говорун", "Максим", "landlord2000@mail.ru",
            //                                                      "+7(977)3311111")
            //                           })
            //        } catch (err) {
            //            console.log("Error creating or updating table in database: " + err)
            //        }
            //    }

        } // ListView

        ListView{
            model: mdl
            spacing: 2
            delegate: Row{
                width: parent.width
                height: 50
                spacing: 2
                Rectangle{
                    width: 250
                    height: parent.height
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        text: friends
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
            header: Row{
                width: parent.width
                height: 50
                spacing: 2
                Rectangle{
                    width: 250
                    height: parent.height
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        text: "friends"
                    }

                }
            } // header: Row
        } // ListView
    } // SwipeView

    PageIndicator{
        id: _indicator
        count: _swipe.count
        currentIndex: _swipe.currentIndex
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
} // Window
