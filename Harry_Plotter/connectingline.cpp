#include "connectingline.h"

connectingLine::connectingLine(QPointF point1, QPointF point2, QString color, QString function, QGraphicsScene* scene, QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    QColor penColor(color);
    QPen pen(penColor);
    this->setPen(pen);

    this->setLine(point1.x(), point1.y(), point2.x(), point2.y());
    setAcceptHoverEvents(true);

    functionText->setDefaultTextColor(color);
    functionText->setPlainText(function);
    functionText->setX(70);
    functionText->setY(20);
    scene->addItem(functionText);
    functionText->setVisible(false);
}

void connectingLine::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    functionText->setVisible(true);
}

void connectingLine::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    functionText->setVisible(false);
}
