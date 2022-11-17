#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "figure.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    QGraphicsScene *scene;
    int numGeometry;

protected:
    //void mousePressEvent(QMouseEvent *event)override;
    void mouseDoubleClickEvent(QMouseEvent *event)override;
private slots:
    void reDraw();
    void deleteFigure(Figure *fig);

};
#endif // MAINWINDOW_H
