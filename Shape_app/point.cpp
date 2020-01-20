#include "point.h"

Point::Point(QPointF representedPoint, QPointF systemPoint, QString color, QGraphicsScene* scene, QGraphicsItem *parent) : QGraphicsEllipseItem(parent), scene(scene)
//x i y su vrijednosti koje tocka reprezentira (potrebne zbog ispisa na ekranu nakon prelaska misa po tocki)
//x_ i y_ su vrijednosti u pixelima gdje je tocka smjestena na sceni
{
    QPen pen(color);
    pen.setWidth(2);
    this->setPen(pen);

    this->setRect(-radius/2, -radius/2, radius, radius);
    this->setPos(systemPoint.x(), systemPoint.y());
    setAcceptHoverEvents(true);

    coordinateText = new QGraphicsTextItem();
    coordinateText->setDefaultTextColor(color);
    coordinateText->setPlainText("(" + QString::number(representedPoint.x()) + "," + QString::number(representedPoint.y()) + ")");
    coordinateText->setX(this->scenePos().x()+5);
    coordinateText->setY(this->scenePos().y()-25);
    scene->addItem(coordinateText);
    coordinateText->setVisible(false);
}


void Point::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{ 
    coordinateText->setVisible(true);
}

void Point::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    coordinateText->setVisible(false);
}
