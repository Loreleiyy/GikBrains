import QtQuick 2.15
import QtQuick.LocalStorage 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0


import "DBFunctions.js" as DBFunctions
Item {

    property int cellHorizontalSpacing : 10
    property var db
    property int intEdit: 1




    TableView{              // TableView на qt 5.15 не даёт выделять
        id: _table1
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        model:     TableModel{
            id: _model1

            TableModelColumn{display: "id"}
            TableModelColumn{display: "first_name"}
            TableModelColumn{display: "last_name"}
            TableModelColumn{display: "email"}
            TableModelColumn{display: "phone"}
            rows: []
        }

        delegate: Rectangle{
            implicitWidth: {Math.max(100, cellHorizontalSpacing + _innerText.width + cellHorizontalSpacing)}
            implicitHeight: 50
            border.width: 1
            Text{
                id: _innerText
                text: display
                anchors.centerIn: parent
            }
        } // Rectangle
    } // TableView

    Dialog{
        id: _dialog
        anchors.centerIn: parent
        title: "add person"
        standardButtons: Dialog.Ok | Dialog.Cancel
        Column{
            anchors.fill: parent
            spacing: 5
            TextField{
                id: firstName
                placeholderText: "Имя"
            }
            TextField{
                id: lastName
                placeholderText: "Фамилия"
            }
            TextField{
                id: email
                placeholderText: "E-mail"
            }
            TextField{
                id: phone
                placeholderText: "Телефон"
            }
        } // Column
        onAccepted: {
            try{
                db.transaction((tx) => {
                                   var resObj = DBFunctions.addContact(tx, firstName.text,
                                             lastName.text, email.text,
                                             phone.text);

                                   console.log(resObj.contact_id);
                                   if(resObj.rowsAffected !== 0){
                                       _model1.appendRow({
                                             id: resObj.contact_id,
                                             first_name: firstName.text,
                                             last_name: lastName.text,
                                             email: email.text,
                                             phone: phone.text})
                                   }
                               }) // db.transaction
            }catch(err){
                console.log("Error creating or updating table in database: " + err)
            }

        } // onAccepted
    } // Dialog

    Button{
        id: _addPerson
        text: "Добавить человека"
        width: 150
        height: 30
        visible: true
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: _dialog.open()
    }


        TextField{
            id: idEdit
            anchors.right: parent.right
            y: parent.height - _edit.height * 3
            placeholderText: "Введите id строки"
        }

    Button{
        id: _edit
        text: "Изменить строку"
        width: 150
        height: 30
        visible: true
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        onClicked: {
            intEdit = parseInt(idEdit.text);

        }
    }

//    Dialog{
//        id: _dialogEdit
//        anchors.centerIn: parent
//        title: "Редактировать"
//        standardButtons: Dialog.Ok | Dialog.Cancel        // попытка в изменении значений
//        Column{
//            anchors.fill: parent
//            spacing: 5
//            TextField{
//                id: firstNameEdit

//                text: _model1.getRow(intEdit).first_name


//            }
//            TextField{
//                id: lastNameEdit
//                text: _model1.getRow(intEdit).last_name
//            }
//            TextField{
//                id: emailEdit
//                text: _model1.getRow(intEdit).email
//            }
//            TextField{
//                id: phoneEdit
//                text: _model1.getRow(intEdit).phone
//            }
//        } // Column

//        onAccepted: {
//            try{
//                db.transaction((tx) => {
//                                   if(firstNameEdit.text != _model1.getRow(intEdit).first_name){
//                                       DBFunctions.setContact(tx, "contacts", intEdit, "first_name", firstNameEdit.text)
//                                   }
//                                   if(lastNameEdit.text != _model1.getRow(intEdit).last_name){
//                                       DBFunctions.setContact(tx, "contacts", intEdit, "last_name", lastNameEdit.text)
//                                   }
//                                   if(emailEdit.text != _model1.getRow(intEdit).email){
//                                       DBFunctions.setContact(tx, "contacts", intEdit, "email", emailEdit.text)
//                                   }
//                                   if(phoneEdit.text != _model1.getRow(intEdit).phone){
//                                       DBFunctions.setContact(tx, "contacts", intEdit, "phone", phoneEdit.text)
//                                   }
//                               })
//            }
//            catch(err){
//                console.log("Error updating table: " + err)
//            }



//            _model1.setRow(intEdit,{
//                               first_name: firstNameEdit.text,
//                               last_name: lastNameEdit.text,
//                               email: emailEdit.text,
//                               phone: phoneEdit.text
//                           })
//        }
//    }

    Component.onCompleted: {
        var data_array = ListModel
        db = LocalStorage.openDatabaseSync("DBExample", "1.0", "Пример локальной базы данных", 1024);
        try{
            db.transaction(DBFunctions.createSimpleTable);
            db.transaction((tx) => { DBFunctions.readContacts(tx) })

        }catch(err){
            console.log("Error creating or updating table in database: " + err)
        }
    }

}
