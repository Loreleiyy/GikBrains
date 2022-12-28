import QtQuick 2.15
import QtQuick.LocalStorage 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0


import "DBFunctions.js" as DBFunctions
Item {

    property int cellHorizontalSpacing : 10
    property var db





    TableView{
        id: _table2
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        model:     TableModel{
            id: _model2

            TableModelColumn{display: "rowid"}
            TableModelColumn{display: "name"}
            TableModelColumn{display: "surname"}
            TableModelColumn{display: "friends"}
            rows: []
        }

        delegate: Rectangle{
            implicitWidth: {Math.max(100, cellHorizontalSpacing + _innerText2.width + cellHorizontalSpacing)}
            implicitHeight: 50
            border.width: 1
            Text{
                id: _innerText2
                text: display
                anchors.centerIn: parent
            }
        } // Rectangle
    } // TableView

    Dialog{
        id: _dialog2
        anchors.centerIn: parent
        title: "add person"
        standardButtons: Dialog.Ok | Dialog.Cancel
        Column{
            anchors.fill: parent
            spacing: 5
            TextField{
                id: name
                placeholderText: "Имя"
            }
            TextField{
                id: surName
                placeholderText: "Фамилия"
            }
            TextField{
                id: friends
                placeholderText: "Друзья"
            }

        } // Column
        onAccepted: {
            try{
                db.transaction((tx) => {
                                   var resObj = DBFunctions.addContact2(tx, name.text,
                                             surName.text, friends.text);

                                   console.log(resObj.id);
                                   if(resObj.rowsAffected !== 0){
                                       _model2.appendRow({
                                             rowid: resObj.id,
                                             name: name.text,
                                             surname: surName.text,
                                             friends: friends.text})
                                   }
                               }) // db.transaction
            }catch(err){
                console.log("Error creating or updating table in database: " + err)
            }

        } // onAccepted
    } // Dialog

    Button{
        id: _addPerson2
        text: "Добавить человека"
        width: 150
        height: 30
        visible: true
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: _dialog2.open()
    }

    Button{
        id: _edit2
        text: "Изменить строку"
        width: 150
        height: 30
        visible: true
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    Component.onCompleted: {
        var data_array = ListModel
        db = LocalStorage.openDatabaseSync("DBExample2", "1.0", "Пример локальной базы данных 2", 1024);
        try{
            db.transaction(DBFunctions.createSimpleTable2);
            db.transaction((tx) => { DBFunctions.readContacts2(tx) })

        }catch(err){
            console.log("Error creating or updating table in database: " + err)
        }
    }

}
