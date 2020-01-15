#include "coordinatesystem.h"

using namespace std;

coordinateSystem::coordinateSystem(QGraphicsScene *scene, QGraphicsItem *parent) : QGraphicsItemGroup(parent)
{
    QPen pen(Qt::gray);
    QGraphicsRectItem* rectangle = new QGraphicsRectItem();
    rectangle->setPen(pen);
    rectangle->setRect(MainWindow::x1, MainWindow::y1, scene->width()-(MainWindow::x1+MainWindow::x2), scene->height()-(MainWindow::y1+MainWindow::y2));
    this->addToGroup(rectangle);
}

int firstDigit(double n) //vraca prvu znamenku razlicitu od nule
{
    if(n >= 1)
        n = n/pow(10, int(log10(n)));
    else
        while(n < 1)
            n *= 10;
    return int(n);
}

double findMultiplier(double n) //za n, vraca broj s kojim trebamo podijeliti n kako bismo dobili jednoznamenkasti broj(zanemarujuci decimale) - npr. za 168 je 100, za 0.053 je 0.01
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

int numberSpaces(double len) //vraca ukupan broj razmaka
{
    int digit = firstDigit(len);
    if(digit < 6){               //osiguravamo da broj razmaka izmedu rubnih tickova bude između 5 i 9, ovisno o granicama
        if(digit == 1)
            digit = 5;
        else if(digit == 2)
            digit *= 4;       
        else if(digit == 3 || digit == 4)
            digit *= 2;
    }
    return digit + 2;
}

double findStep(double len) //vraca vrijednost razmaka izmedu dva ticka - ne njegovu duljinu u pixelima, nego duljinu koju on prikazuje u koordinatnom sustavu
{
    double num = firstDigit(len)*findMultiplier(len);
    return num/(numberSpaces(len)-2);
}


tuple<tuple<double, double, double, double>, QGraphicsItemGroup*> coordinateSystem::init(QGraphicsScene *scene, double xStart, double xEnd, double yStart, double yEnd)
{
    double xLen = xEnd - xStart;
    double yLen = yEnd - yStart;

    int xSpaces = numberSpaces(xLen);
    int ySpaces = numberSpaces(yLen);

    double xStep = findStep(xLen);
    double yStep = findStep(yLen);

    double xBeginning = (bool(fmod(xStart,xStep)) && xStart > 0) ? int(xStart/xStep)*xStep :(int(xStart/xStep)-1)*xStep; //broj koji predstavlja tocka u ishodistu koordinatnog sustava
    double yBeginning = (bool(fmod(yStart,yStep)) && yStart > 0) ? int(yStart/yStep)*yStep :(int(yStart/yStep)-1)*yStep;

    while((xEnd-(xBeginning+xSpaces*xStep)) >= 0) //npr. za raspon od 0 do 3.9, xSpaces bi bio 3*2+2=8, xStep 3/6=0.5, a xBeginning -0.5 te bi koordinatni sustav prikazivao vrijednosti za x od -0.5 do -0.5+8*0.5=3.5
        xSpaces += 1;                             //zato po potrebi dodajemo nove razmake, u najgorem slucaju moze ih biti ukuno 13 (npr. za raspon od 0 do 2.8) jer je xStep 0.25 i treba se jos triput naknadno dodati da "pokrije" 2.8
    while((yEnd-(yBeginning+ySpaces*yStep)) >= 0)
        ySpaces += 1;

    int xWidth = int((scene->width()-(MainWindow::x1+MainWindow::x2))/xSpaces); //kada znamo konacan broj razmaka racunamo koliki je razmak izmedu dva ticka u pixelima
    int yWidth = int((scene->height()-(MainWindow::y1+MainWindow::y2))/ySpaces);

    double xTick = xBeginning;
    double yTick = yBeginning;

    QGraphicsItemGroup* grid = new QGraphicsItemGroup();
    QPen penGrid(QColor("#666666"));
    penGrid.setStyle(Qt::DotLine);
    QPen pen(Qt::gray);

    for(int i = 1; i < xSpaces; ++i){
        QGraphicsLineItem* lineTick = new QGraphicsLineItem(); //tickovi
        lineTick->setPen(pen);
        lineTick->setLine(MainWindow::x1 + i*xWidth, scene->height()-MainWindow::y2-5, MainWindow::x1 + i*xWidth, scene->height()-MainWindow::y2+5);
        this->addToGroup(lineTick);

        QGraphicsLineItem* lineGrid = new QGraphicsLineItem(); //linije grida
        lineGrid->setPen(penGrid);
        lineGrid->setLine(MainWindow::x1 + i*xWidth, scene->height()-MainWindow::y2, MainWindow::x1 + i*xWidth, MainWindow::y1);
        grid->addToGroup(lineGrid);

        QGraphicsTextItem* number = new QGraphicsTextItem(); //brojevi uz tickove
        xTick += xStep;
        number->setDefaultTextColor(Qt::gray);
        number->setPlainText(QString::number(xTick));        
        number->setPos(MainWindow::x1 + i*xWidth - number->boundingRect().width()/2, scene->height()-MainWindow::y2+5);
        this->addToGroup(number);
    }

    for(int i = 1; i < ySpaces; ++i){ //slicni postupak za y os
        QGraphicsLineItem* lineTick = new QGraphicsLineItem();
        lineTick->setPen(pen);
        lineTick->setLine(MainWindow::x1 - 5, scene->height()-MainWindow::y2 - i*yWidth, MainWindow::x1 + 5, scene->height()-MainWindow::y2 - i*yWidth);
        this->addToGroup(lineTick);

        QGraphicsLineItem* lineGrid = new QGraphicsLineItem();
        lineGrid->setPen(penGrid);
        lineGrid->setLine(MainWindow::x1, scene->height()-MainWindow::y2 - i*yWidth, scene->width()-MainWindow::x2, scene->height()-MainWindow::y2 - i*yWidth);
        grid->addToGroup(lineGrid);

        QGraphicsTextItem* number = new QGraphicsTextItem();
        yTick += yStep;
        number->setDefaultTextColor(Qt::gray);
        number->setPlainText(QString::number(round(yTick*pow(10,10))/pow(10,10)));
        number->setPos(MainWindow::x1-5 - number->boundingRect().width(), scene->height()-MainWindow::y2 - i*yWidth - number->boundingRect().height()/2);
        this->addToGroup(number);
    }

    scene->addItem(this);
    scene->addItem(grid);

    return make_tuple(make_tuple(xBeginning, yBeginning, xWidth/xStep, yWidth/yStep), grid); //funkcija vraca informacije o ishodistu koordinatnog sustava, te o kvocijentu duljine razmaka izmedu dva ticka u pixelima i vrijednosti koju taj razmak reprezentira u koord. sustavu kako bismo mogli iscrtavati linije i tocke
                                                                                             //fja vraca i grid koji ce se prikazivati po potrebi, u ovisnosti o checkBoxu Show grid
}

