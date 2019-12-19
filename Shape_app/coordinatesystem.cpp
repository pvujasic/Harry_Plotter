#include "coordinatesystem.h"

coordinateSystem::coordinateSystem(QGraphicsScene *scene, QGraphicsItem *parent) : QGraphicsItemGroup(parent)
{
    QGraphicsRectItem* rectangle = new QGraphicsRectItem();
    rectangle->setRect(MainWindow::x1, MainWindow::y1, scene->width()-(MainWindow::x1+MainWindow::x2), scene->height()-(MainWindow::y1+MainWindow::y2));
    this->addToGroup(rectangle);
}

int firstDigit(double n)
{
    if(n >= 1)
        n = n/pow(10, int(log10(n)));
    else
        while(n < 1)
            n *= 10;
    return int(n);
}

double findMultiplier(double n)
{
    double multiplier = 1;
    if(n >= 1)
        multiplier = pow(10, int(log10(n)));
    else
        while(n < 1)
        {
            n *= 10;
            multiplier /= 10;
        }
    return multiplier;
}

int numberSpaces(double len)
{
    int digit = firstDigit(len);
    if(digit < 6){               //osiguravamo da broj razmaka među tickovima bude između 5 i 9, ovisno o granicama
        if(digit == 1)
            digit = 5;
        else if(digit == 2)
            digit *= 4;       
        else if(digit == 3 || digit == 4)
            digit *= 2;
    }
    return digit + 2;
}

double findStep(double len)
{
    double num = firstDigit(len)*findMultiplier(len);
    return num/(numberSpaces(len)-2);
}


tuple<double, double, double, double> coordinateSystem::init(QGraphicsScene *scene, double xStart, double xEnd, double yStart, double yEnd)
{
    double xLen = xEnd - xStart;
    double yLen = yEnd - yStart;

    int xSpaces = numberSpaces(xLen);
    int ySpaces = numberSpaces(yLen);

    double xStep = findStep(xLen);
    double yStep = findStep(yLen);

    double xBeginning = (bool(fmod(xStart,xStep)) && xStart > 0) ? int(xStart/xStep)*xStep :(int(xStart/xStep)-1)*xStep;
    double yBeginning = (bool(fmod(yStart,yStep)) && yStart > 0) ? int(yStart/yStep)*yStep :(int(yStart/yStep)-1)*yStep;

    while((xEnd-(xBeginning+xSpaces*xStep)) >= 0)
        xSpaces += 1;
    while((yEnd-(yBeginning+ySpaces*yStep)) >= 0)
        ySpaces += 1;

    int xWidth = int((scene->width()-(MainWindow::x1+MainWindow::x2))/xSpaces);
    int yWidth = int((scene->height()-(MainWindow::y1+MainWindow::y2))/ySpaces);

    double xTick = xBeginning;
    double yTick = yBeginning;

    for(int i = 1; i < xSpaces; ++i){
        QGraphicsLineItem* line = new QGraphicsLineItem();
        line->setLine(MainWindow::x1 + i*xWidth, scene->height()-MainWindow::y2-5, MainWindow::x1 + i*xWidth, scene->height()-MainWindow::y2+5);
        this->addToGroup(line);

        QGraphicsTextItem* number = new QGraphicsTextItem();
        xTick += xStep;
        number->setPlainText(QString::number(xTick));        
        number->setPos(MainWindow::x1 + i*xWidth - number->boundingRect().width()/2, scene->height()-MainWindow::y2+5);
        this->addToGroup(number);
    }

    for(int i = 1; i < ySpaces; ++i){
        QGraphicsLineItem* line = new QGraphicsLineItem();
        line->setLine(MainWindow::x1 - 5, scene->height()-MainWindow::y2 - i*yWidth, MainWindow::x1 + 5, scene->height()-MainWindow::y2 - i*yWidth);
        this->addToGroup(line);

        QGraphicsTextItem* number = new QGraphicsTextItem();
        yTick += yStep;
        number->setPlainText(QString::number(yTick));        
        number->setPos(MainWindow::x1-5 - number->boundingRect().width(), scene->height()-MainWindow::y2 - i*yWidth - number->boundingRect().height()/2);
        this->addToGroup(number);
    }


    scene->addItem(this);
    return make_tuple(xBeginning, yBeginning, xWidth/xStep, yWidth/yStep);
}

