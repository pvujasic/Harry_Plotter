#include "connectingline.h"

using namespace std;

connectingLine::connectingLine(QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    QPen pen(Qt::gray);
    pen.setWidth(2);
    this->setPen(pen);
}

void connectingLine::initLine(QGraphicsScene *scene, double x1, double y1, double x2, double y2, tuple<double, double, double, double> system_Info)
{
    double xStart = get<0>(system_Info);
    double yStart = get<1>(system_Info);
    double xStep = get<2>(system_Info);
    double yStep = get<3>(system_Info);

    this->setLine(MainWindow::x1 + (x1-xStart)*xStep, scene->height()-MainWindow::y2-(y1-yStart)*yStep,
                  MainWindow::x1 + (x2-xStart)*xStep, scene->height()-MainWindow::y2-(y2-yStart)*yStep);
    scene->addItem(this);
}

