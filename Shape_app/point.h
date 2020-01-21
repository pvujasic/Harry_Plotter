#ifndef POINT_H
#define POINT_H

#include "mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

class Point : public QGraphicsEllipseItem
{
public:
    Point(QPointF representedPoint, QPointF systemPoint, QString color, QGraphicsScene* scene, QGraphicsItem* parent = nullptr);

private:
    const double radius = 8;
    QGraphicsTextItem* coordinateText = new QGraphicsTextItem();
    QGraphicsScene* scene;

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};

#endif // POINT_H
