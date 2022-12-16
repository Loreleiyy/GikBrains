#include "counting.h"
#include <QDebug>

Counting::Counting(QObject *parent)
    : QObject{parent}
{
    Xvector = {7, 31, 61, 99, 129, 178, 209};
    Yvector = {13, 10, 9, 10, 12, 20, 26};
    methodLeastSquares();
}

int Counting::getXvector(int index)
{
    return Xvector[index];
}

int Counting::getYvector(int index)
{
    return Yvector[index];
}

int Counting::getSize()
{
    return Xvector.size();
}

void Counting::methodLeastSquares()
{
    int sumX =0;
    int sumY = 0;
    int sumxy = 0;
    int sumX2 = 0;
    double size = Xvector.size();
    for (int i = 0; i < size; ++i) {
        sumX += Xvector[i];
        sumY += Yvector[i];
        sumxy += Xvector[i] * Yvector[i];
        sumX2 += Xvector[i] * Xvector[i];
    }
    a = (size * sumxy - sumX * sumY) / (size * sumX2 - sumX * sumX);
    b = (sumY - a * sumX)/size;
    qDebug() << a << " b " << b;                    // y = ax+b
}

double Counting::getYLeastSquares(int index)
{
    return a*Xvector[index] + b;
}
