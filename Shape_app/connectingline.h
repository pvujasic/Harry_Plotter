#ifndef CONNECTINGLINE_H
#define CONNECTINGLINE_H

#include "mainwindow.h"


class connectingLine : public QGraphicsLineItem
{
public:
    connectingLine(double x1, double y1, double x2, double y2, QString color, QGraphicsItem* parent = nullptr);
};

#endif // CONNECTINGLINE_H
