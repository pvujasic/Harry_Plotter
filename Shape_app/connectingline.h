#ifndef CONNECTINGLINE_H
#define CONNECTINGLINE_H

#include "mainwindow.h"


class connectingLine : public QGraphicsLineItem
{
public:
    connectingLine(QGraphicsItem* parent = nullptr);
    void initLine(QGraphicsScene* scene, double x1, double y1, double x2, double y2, std::tuple<double, double, double, double> system_Info);
};

#endif // CONNECTINGLINE_H
