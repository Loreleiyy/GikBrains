#pragma once

#include <QObject>
#include <QVector>
#include <QtQml/qqml.h>
#include <QMap>

class Description: public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
public:
    Description(QObject *parent = nullptr);
    enum type{
        LINE,
        SIN,
        MODULE,
        DEGREE2,
        LOG2
    };
    Q_ENUM(type)

private:
    QString color;
    QString name;
    QVector<double> Xvector;
    QVector<double> Yvector;
    const int sumX = 51;
    QMap<QString, type> mapType;

    void sin();
    void line();
    void module();
    void degree2();
    void log2();

public:
    Q_INVOKABLE QString getColor();
    Q_INVOKABLE QString getName();
    Q_INVOKABLE void setColor(QString newcolor);
    Q_INVOKABLE void setName(QString newname);
    Q_INVOKABLE double getX(int index);
    Q_INVOKABLE double getY(int index);
    Q_INVOKABLE void setCharts(QString newchart);

signals:
    void colorChanged();
    void nameChanged();
};


