#include "colormanager.h"
#include<QDebug>
ColorManager::ColorManager()
{

}

QString selectColor(int colorNumber) //prvih 5 boja je za funkcije, drugih 5 za datoteke
{
    switch(colorNumber)
    {
        case(0):
            return QString("#ffc400");
        case(1):
            return QString("#ff7f2e");
        case(2):
            return QString("#ff2b8f");
        case(3):
            return QString("#5993ff");
        case(4):
            return QString("#32f0a3");
        case(5):
            return QString("#7ddb9b");
        case(6):
            return QString("#829dd1");
        case(7):
            return QString("#db72a4");
        case(8):
            return QString("#e69460");
        default:
            return QString("#edd37b");
    }
}

int getIndex(QString colorName)
{
    if(colorName == "#ffc400" ||colorName ==  "#7ddb9b")
        return 0;
    else if(colorName == "#ff7f2e" ||colorName ==  "#829dd1")
        return 1;
    else if(colorName == "#ff2b8f" ||colorName ==  "#db72a4")
        return 2;
    else if(colorName == "#5993ff" ||colorName ==  "#e69460")
        return 3;
    else if(colorName == "#32f0a3" ||colorName ==  "#edd37b")
        return 4;

            qDebug()<< "Color not in range";

}


QString ColorManager::getFileColor()
{
    for(int i = 0; i < 5; ++i)
        if(fileColors[i] == false){
            fileColors[i] = true;
            return selectColor(i+5);
    }
    qDebug() << "previse boja";
}

QString ColorManager::getFunctionColor()
{
    for(int i = 0; i < 5; ++i)
        if(functionColors[i] == false){
            functionColors[i] = true;
            return selectColor(i);
        }
    qDebug() << "previse boja";
}

void ColorManager::releaseFunctionColor(QString color)
{
    int index = getIndex(color);
    functionColors[index] = false;
}


void ColorManager::releaseFileColor(QString color)
{
    int index = getIndex(color);
    fileColors[index] = false;
}

void ColorManager::reset()
{
    for(int i = 0; i < 5; ++i)
    {
        fileColors[i] = false;
        functionColors[i] = false;
    }
}
