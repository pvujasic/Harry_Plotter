#include "point.h"

Point::Point(double x, double y, double x_, double y_, QString color, QGraphicsScene* scene, QGraphicsItem *parent) : QGraphicsEllipseItem(parent), scene(scene)
//x i y su vrijednosti koje tocka reprezentira (potrebne zbog ispisa na ekranu nakon prelaska misa po tocki)
//x_ i y_ su vrijednosti u pixelima gdje je tocka smjestena na sceni
{
    QPen pen(color);
    pen.setWidth(2);
    this->setPen(pen);

    this->setRect(-radius/2, -radius/2, radius, radius);
    this->setPos(x_, y_);
    setAcceptHoverEvents(true);

    coordinateText = new QGraphicsTextItem();
    coordinateText->setDefaultTextColor(color);
    coordinateText->setPlainText("(" + QString::number(x) + "," + QString::number(y) + ")");
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
