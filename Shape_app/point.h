#ifndef POINT_H
#define POINT_H

#include "mainwindow.h"

class Point : public QGraphicsEllipseItem
{
public:
    Point(double x, double y, double x_, double y_, QGraphicsScene* scene, QGraphicsItem* parent = nullptr);

private:
    const double radius = 10;
    double x;
    double y;
    QGraphicsTextItem* coordinateText;
    QGraphicsScene* scene;

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};

#endif // POINT_H
