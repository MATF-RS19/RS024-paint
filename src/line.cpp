#include "line.h"
#include <QGraphicsSceneMouseEvent>
#include <iostream>
Line::Line()
{
}

QRectF Line::boundingRect() const
{
    return QRectF(0,0,1000,1000);
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    for(QPointF p: points){
        painter->drawEllipse(p,1,1);
    }
}

void Line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    points.push_back(event->pos());
    update();
}

void Line::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    points.push_back(event->pos());
    update();

}

void Line::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    points.push_back(event->pos());
    update();

}
