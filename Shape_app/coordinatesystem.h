#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "mainwindow.h"

class coordinateSystem : public QGraphicsItemGroup
{
public:
    explicit coordinateSystem(QGraphicsScene *scene, QGraphicsItem* parent = nullptr);
    std::tuple<double, double, double, double> init(QGraphicsScene* scene, double xStart, double xEnd, double yStart, double yEnd);
};

#endif // COORDINATESYSTEM_H
