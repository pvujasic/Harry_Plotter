#ifndef CONNECTINGLINE_H
#define CONNECTINGLINE_H

#include "mainwindow.h"

class connectingLine : public QGraphicsLineItem
{
public:
    connectingLine(QPointF point1, QPointF point2, QString color, QString function, QGraphicsScene* scene, QGraphicsItem* parent = nullptr);

private:
    QGraphicsTextItem* functionText = new QGraphicsTextItem();
    QGraphicsScene* scene;

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};

#endif // CONNECTINGLINE_H
