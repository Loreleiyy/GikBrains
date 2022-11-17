#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>


class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)
public:

    explicit Figure(int x, int y, int geo, QObject *parent = nullptr);
    void setBrush(QBrush brush);

private:
    enum Geometry {RECTANGLE = 0,
                  ELLIPS,
                  STAR};

    signed int x,y;
    int height, width;
    Geometry geometry;
    bool moving;

    QBrush brush;
    QPoint bPoint;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    QRectF boundingRect()const override;

signals:
    void reDraw();
    void deleteFigure(Figure *fig);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
};

#endif // FIGURE_H
