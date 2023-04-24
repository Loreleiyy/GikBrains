#include "mainwindow.h"


#include <QMouseEvent>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    QPainter p;
    p.drawRect(0,0,200,100);
    numGeometry = 0;


}

MainWindow::~MainWindow()
{
}

//void MainWindow::mousePressEvent(QMouseEvent *event)
//{


//}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !scene->mouseGrabberItem()){
        int x = (event->pos().x());       // window size
        int y = (event->pos().y());       // window size
        Figure *fig = new Figure(x, y, numGeometry, this);
        connect(fig, &Figure::reDraw, this, &MainWindow::reDraw);
        connect(fig, &Figure::deleteFigure, this, &MainWindow::deleteFigure);

        scene->addItem(fig);

        ++numGeometry;
    }
}

void MainWindow::reDraw()
{
    scene->update();
    update();
}

void MainWindow::deleteFigure(Figure *fig)
{
    scene->removeItem(fig);
}



