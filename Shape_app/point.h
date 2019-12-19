#ifndef POINT_H
#define POINT_H

#include "mainwindow.h"

class Point : public QGraphicsEllipseItem
{
public:
    Point(QGraphicsItem* parent = nullptr);
    void initPoint(QGraphicsScene* scene, double x_, double y_, std::tuple<double, double, double, double> system_Info);

    double x;
    double y;
    const int radius = 10;
};

#endif // POINT_H
