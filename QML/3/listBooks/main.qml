import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    ListModel{
        id: _library
        ListElement{
            cover: "img/1_Harry"                             // иконка
            title: "Гарри Поттер и философский камень"       // название
            genre: "Фентези"                                 // жанр
            author: "Роулинг Дж."                            // автор
        }
        ListElement{
            cover: "img/2_Apostate"
            title: "Отступник"
            genre: "Фентези"
            author: "Сальваторе Роберт"
        }
        ListElement{
            cover: "img/3_Panchin"
            title: "Защита от темных искусств"
            genre: "Наука и техника"
            author: "Панчин Александр"
        }
        ListElement{
            cover: "img/4_Dokinz"
            title: "Эгоистичный ген"
            genre: "Наука и техника"
            author: "Ричард Докинз"
        }
        ListElement{
            cover: "img/5_Knut"
            title: "Искусство программирования"
            genre: "Программирование"
            author: "Д. Кнут"
        }
        ListElement{
            cover: "img/6_Algoritm"
            title: "Грокаем алгоритмы"
            genre: "Программирование"
            author: "Адитья Бхаргава"
        }
    }

    ListView{
        id: _view
        anchors.fill: parent
        model: _library
        spacing: 1
        header: Rectangle{
            width: parent.width
            height: 40
            color: "yellow"
            Text{
                anchors.centerIn: parent
                text: "My library"
            }
        }
        footer: Rectangle{
            width: parent.width
            height: 40
            color: "blue"
            Text{
                anchors.centerIn: parent
                text: "Разработчик: Вадим Бояров"
            }
        }
        section.delegate: Rectangle{
            width: parent.width
            height: 30
            color: "gray"
            Text{
                anchors.centerIn: parent
                text: section
                color: "red"
                //font.weight: Font.bold
            }
        }
        section.property: "genre"

        delegate: Rectangle{
            width: _view.width
            height: 45
            border.width: 1
            border.color: "darkgreen"
            color: "green"

            Image{
                id: _img
                width: 40
                height: 40
                source: cover
            }
            Column{
                anchors.fill: parent


                Row{

                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{text: "Название "}
                    Text{text: title}
                    spacing: 60
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{text: "Автор"}
                    Text{text: author}
                    spacing: 60
                }
            }
        }
    }
}
