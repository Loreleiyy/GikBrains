import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")
    Text{
        x: parent.width / 2 - 100

        text: "Регистрация"
        color: "red"
    }
    Row{
        x: 10
        y: 50
        spacing: 60
    Column{


        spacing: 40

        TextField{
            id: _name
            Text{

                text: "Имя"
                anchors.bottom: parent.top
            }
        }

        ComboBox{
            id: _youMale
            Text{

                text: "Пол"
                anchors.bottom: parent.top
            }
            model: ["муж", "жен"]
        }
        Slider{
            id: _youAge
            from: 18
            to: 99
            stepSize: 1
            Text{
                text: "Возраст " + parent.value
                anchors.bottom: parent.top
            }
        }
        ComboBox{
            id: _youEducation
            Text{
                text: "Уровень образования"
                anchors.bottom: parent.top
            }
            model: ["9 классов", "11 классов", "Среднетехничекое", "Высшее"]
        }
        Rectangle{
            width: 200
            height: 100
            border.color: "black"
            TextEdit{
                id: _aboutMe
                anchors.fill: parent
                wrapMode: TextEdit.Wrap
                anchors.margins: 5
            }
            Text{
                text: "О себе"
                anchors.bottom: parent.top
            }
        }
    }

    Column{

        spacing: 40
        ComboBox{
            id: _country
            Text{
                text: "Страна"
                anchors.bottom: parent.top
            }
            model: ["Россия", "США", "Китай", "Грузия", "Великобритания", "Франция", "Италия", "Казахстан", "Германия", "Япония"]
        }
        TextField{
            id: _city
            Text{
                text: "Город"
                anchors.bottom: parent.top
            }
        }
        Rectangle{
            width: 200
            height: 100
            border.color: "black"
            TextEdit{
                id: _hobby
                anchors.fill: parent
                wrapMode: TextEdit.Wrap
                anchors.margins: 5
            }
            Text{
                text: "Хобби"
                anchors.bottom: parent.top
            }
        }
    }
    Column{
        spacing: 40
        Text{
            text: "Кого ищите"
        }
        ComboBox{
            id: _searchMale

            Text{
                text: "Пол"
                anchors.bottom: parent.top
            }
            model: ["муж", "жен"]
        }
        Column{
            spacing: 10
            Slider{
                id: _searchMinAge

                from: 18
                to: _searchMaxAge.value
                stepSize: 1
                value: 18
                Text{
                    text: "Минимальный возраст " + parent.value
                    anchors.bottom: parent.top
                }
            }
            Slider{
                id: _searchMaxAge
                from: _searchMinAge.value
                to: 99
                stepSize: 1
                value: 99
                Text{
                    text: "Максимальный  возраст " + parent.value
                    anchors.bottom: parent.top
                }
            }
            ComboBox{
                id: _searchEducation
                Text{
                    text: "Уровень образования"
                    anchors.bottom: parent.top
                }
                model: ["9 классов", "11 классов", "Среднетехничекое", "Высшее"]
        }
    }
}
}
    Button{
        text: "Зарегистрироваться"
        x: parent.width - 150
        y: parent.height - 100
        onClicked: {
            console.log("вы: " + _name.text + " " + _youMale.currentValue + " " + _youAge.value + " "  +
                        _youEducation.currentValue + " " + _country.currentValue + " " + _city.text + " " +
                        _hobby.text + " " + _aboutMe.text)
            console.log("кого ищите: " + _searchMale.currentValue + " минимальный возраст " + _searchMinAge.value +
                        " максимальный возраст " + _searchMaxAge.value + " " + _searchEducation.currentValue)
        }
    }
}

