#include <QDebug>
#include <QtMath>
#include <cmath>            // для log2()


#include "description.h"


Description::Description(QObject *parent): QObject(parent)
{
    color = "red";
    name = "description";
    Xvector.reserve(sumX);
    Yvector.resize(sumX);
    for(int i = 0; i < sumX; ++i){
        Xvector.push_back(i/10.0);
        //qDebug() << Xvector[i];
    }
    mapType["LINE"] = Description::type::LINE;
    mapType["SIN"] = Description::type::SIN;
    mapType["MODULE"] = Description::type::MODULE;
    mapType["DEGREE2"] = Description::type::DEGREE2;
    mapType["LOG2"] = Description::type::LOG2;
    log2();
}

void Description::sin()
{
    for(int i = 0; i < sumX; ++i){
        Yvector[i] =  qSin(Xvector[i]);
    }
}

void Description::line()
{
    for(int i = 0; i < sumX; ++i){
        Yvector[i] = Xvector[i];
    }
}

void Description::module()
{
    for(int i = 0; i < sumX; ++i){
        Yvector[i] = qFabs(Xvector[i] - 2.5);
    }
}

void Description::degree2()
{
    for(int i = 0; i < sumX; ++i){
        Yvector[i] = Xvector[i] * Xvector[i];
    }
}

void Description::log2()
{
    for(int i = 1; i < sumX; ++i){
        Yvector[i] = std::log2(Xvector[i]);
        qDebug() << Yvector[i];
    }
}

QString Description::getColor()
{
    return color;

}

QString Description::getName()
{
    return name;
}

void Description::setColor(QString newcolor)
{
    qDebug() << newcolor;
    color = newcolor;
}

void Description::setName(QString newname)
{
    name = newname;
}

double Description::getX(int index)
{
    return Xvector[index];
}

double Description::getY(int index)
{
    return Yvector[index];
}

void Description::setCharts(QString newchart)
{
    qDebug() << newchart;

    switch (mapType.value(newchart)) {
    case Description::type::LINE:
        line();
        break;
    case Description::type::SIN:
        sin();
        break;
    case Description::type::MODULE:
        module();
        break;
    case Description::type::DEGREE2:
        degree2();
        break;
    case Description::type::LOG2:
        log2();
        break;
    default:
        line();
        break;
    }

}
