#ifndef LINE_H
#define LINE_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <vector>
class Line : public QGraphicsItem
{
public:
    Line();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    QPointF pointB,pointE;
    QLineF m_line;
    std::vector<QPointF> points;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // LINE_H
