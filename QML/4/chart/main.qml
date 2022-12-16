import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtCharts 2.15

// description

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Charts")
    property double desX: 0
    property double desY: 0
    property string desname: description.getName()
    property string descolor: description.getColor()

    Button{
        id: _newLine
        width: 150
        height: 40
        text: "сменить график"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {

            description.setCharts(_charts.currentValue)
            setLine()
            _line.name = _charts.currentValue
        }
}
    ComboBox{
        id: _charts
        width: 150
        height: 40
        anchors.bottom: parent.bottom
        x: 20
        model: ["LINE", "SIN", "MODULE", "DEGREE2", "LOG2"]
    }

        ChartView{
            id: _view
            anchors.fill: parent
            anchors.margins: 50
            antialiasing: true

            LineSeries{
                id: _line
                color: descolor

                axisX: ValueAxis {
                    min: 0
                    max: 5
                }
                axisY: ValueAxis{
                    id: _axisY
                    min: 0
                    max: 5
                }
            }

            Component.onCompleted: _newLine.clicked()
        }


        function setLine(){
            _line.removePoints(0, _line.count)
            var minY = 0
            var maxY = 0
            var i
            if(_charts.currentValue === "LOG2"){
                i = 1
            }
            else{
                i = 0
            }

            for(; i < 51; ++i){
                desX = description.getX(i)
                desY = description.getY(i)
                if(minY > desY)minY = desY
                if(maxY < desY)maxY = desY
                _line.insert(i, desX, desY)
            }
            _axisY.min = minY
            _axisY.max = maxY
        }
}
