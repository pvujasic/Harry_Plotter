#include "connectingline.h"

connectingLine::connectingLine(double x1, double y1, double x2, double y2, QString color, QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    QColor penColor(color);
    QPen pen(penColor);
    this->setPen(pen);

    this->setLine(x1, y1, x2, y2);
}


