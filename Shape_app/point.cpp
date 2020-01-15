#include "point.h"

Point::Point(double x, double y, double x_, double y_, QGraphicsScene* scene, QGraphicsItem *parent) : QGraphicsEllipseItem(parent), x(x), y(y),
    coordinateText(Q_NULLPTR), scene(scene) //x i y su vrijednosti koje tocka reprezentira (potrebne zbog ispisa na ekranu nakon prelaska misa po tocki)
                                            //x_ i y_ su vrijednosti u pixelima gdje je tocka smjestena na sceni
{
    QPen pen(Qt::gray);
    pen.setWidth(2);
    this->setPen(pen);


    this->setRect(-radius/2, -radius/2, radius, radius);
    this->setPos(x_, y_);
    setAcceptHoverEvents(true);
}


void Point::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{ 
    if (!coordinateText)
    {   
        coordinateText = new QGraphicsTextItem();
        coordinateText->setDefaultTextColor(Qt::gray);
        coordinateText->setPlainText("(" + QString::number(x) + "," + QString::number(y) + ")");
        coordinateText->setX(this->scenePos().x()+5);
        coordinateText->setY(this->scenePos().y()-25);
        scene->addItem(coordinateText);
    }

    coordinateText->setVisible(true);
}

void Point::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    if (coordinateText) {
        coordinateText->setVisible(false);
    }
}
