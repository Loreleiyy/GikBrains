import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtCharts 2.15
import Counting 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Least squares")

    Counting{
        id: _couting
    }
    ChartView {
        title: "Метод наименьших квадратов"
        anchors.fill: parent
        antialiasing: true
        ScatterSeries {
            id: _scatter
            name: "Диаграмма рассеяния"


            axisX: ValueAxis {
                min: 0
                max: 230
            }
            axisY: ValueAxis{
                min: 0
                max: 30
            }
        }
        LineSeries{
            id: _line
            name: "Линейная зависимость"
            color: "red"
        }


    }

    Component.onCompleted: {initPoint()
        resultLeastSquares()
    }

    function initPoint(){
        var dX
        var dY
        for(var i = 0; i < _couting.getSize(); ++i){
            dX = _couting.getXvector(i)
            dY = _couting.getYvector(i)
            _scatter.insert(i, dX, dY)
        }
    }
    function resultLeastSquares(){
        var dX
        var dY
        for(var i = 0; i < _couting.getSize(); ++i){
            dX = _couting.getXvector(i)
            dY = _couting.getYLeastSquares(i)
            _line.insert(i, dX, dY)
        }
    }
}
