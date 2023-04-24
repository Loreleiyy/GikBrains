#include "figure.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


Figure::Figure(int ax, int ay, int geo, QObject *parent)
: QObject(parent), QGraphicsItem()
{
    x=0;
    y=0;
    width = 200;
    height = 100;
    brush.setColor(QColor(rand()%256, rand()%256, rand()%256));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    geometry = static_cast<Geometry>(geo % 3);

    setPos(0, 0);
    moving = false;
}

void Figure::setBrush(QBrush brush)
{
    this->brush = brush;
    emit reDraw();
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(brush);
    auto zzz = this->scenePos();
    qDebug() << zzz.x()<< ' ' << zzz.y();
    if(geometry == Geometry::RECTANGLE){
        painter->drawRect(x, y, width, height);
    }
    else if(geometry == Geometry::ELLIPS){
        painter->drawEllipse(x, y, width, height);
    }
    else if(geometry == Geometry::STAR){
        QPolygon pol;
        pol << QPoint(width/2 + x, y) << QPoint(x, height/3 +y) << QPoint(width/4+x, height) <<
               QPoint((width-(width/4)+x), height) << QPoint(width + x, (height-(height/3)+x)) ;
        painter->drawPolygon(pol);
    }
}

QRectF Figure::boundingRect() const
{
    return QRectF(x, y, width, height);
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        moving = true;
        bPoint = event->pos().toPoint();


    }
    else if(event->button() == Qt::RightButton){
        emit deleteFigure(this);
    }
}

void Figure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        moving = false;
        emit reDraw();
    }
}

void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->pos().x() << ' ' <<  event->pos().y();
    if (moving){
        QPoint p = event->pos().toPoint() - bPoint;
        x += p.x();
        y += p.y();
        bPoint = p;
        emit reDraw();
    }
}
