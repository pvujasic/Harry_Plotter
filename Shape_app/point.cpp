#include "point.h"


Point::Point(QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
    QPen pen(Qt::blue);
    pen.setWidth(2);
    this->setPen(pen);
}

void Point::initPoint(QGraphicsScene* scene, double x_, double y_, tuple<double, double, double, double> system_Info)
{
    x = x_;
    y = y_;
    double xStart = get<0>(system_Info);
    double yStart = get<1>(system_Info);
    double xStep = get<2>(system_Info);
    double yStep = get<3>(system_Info);

    this->setRect(MainWindow::x1 + (x-xStart)*xStep-radius/2, scene->height()-MainWindow::y2-(y-yStart)*yStep-radius/2, radius, radius);
    scene->addItem(this);
}
