#include "connectingline.h"

connectingLine::connectingLine(double x1, double y1, double x2, double y2, QString color, QString function, QGraphicsScene* scene, QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    QColor penColor(color);
    QPen pen(penColor);
    this->setPen(pen);

    this->setPos(x1 + (x2 - x1)/2, y1 + (y2 - y1)/2);
    this->setLine(-(x2 - x1)/2, -(y2 - y1)/2, (x2 - x1)/2, (y2 - y1)/2);
    setAcceptHoverEvents(true);

    if(function != "")
    {
    functionText->setDefaultTextColor(color);
    functionText->setPlainText(function);
    functionText->setX(this->scenePos().x()+20);
    functionText->setY(this->scenePos().y()-20);
    scene->addItem(functionText);
    functionText->setVisible(false);
    }
}

void connectingLine::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    functionText->setVisible(true);
}

void connectingLine::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    functionText->setVisible(false);
}
