#ifndef COUNTING_H
#define COUNTING_H

#include <QObject>
#include <QVector>
#include <QtQml/qqml.h>

class Counting : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Counting(QObject *parent = nullptr);
private:
    QVector<int> Xvector;
    QVector<int> Yvector;
    double a;
    double b;
public:
    Q_INVOKABLE int getXvector(int index);
    Q_INVOKABLE int getYvector(int index);
    Q_INVOKABLE int getSize();
    Q_INVOKABLE void methodLeastSquares();
    Q_INVOKABLE double getYLeastSquares(int index);
signals:

};

#endif // COUNTING_H
