#include "utility.h"
#include <iostream>
#include <QDebug>


Utility::Utility()
{

}

bool Utility::compareDoubles(double a, double b)
{
   double diff = a - b;
   return (diff < std::numeric_limits<double>::epsilon()) && (diff > -std::numeric_limits<double>::epsilon());
}

QVector<double> Utility::linspace(double start, double end, int num) //po uzoru na pythonovu fju linspace, vraca vector jednoliko rasporedenih brojeva u zadanom intervalu
{
    QVector<double> linspaced(num);
    double delta = (end - start)/(num - 1);

    for(int i = 0; i < num-1; ++i)
      {
        linspaced[i] = start + delta * i;
      }

    linspaced[num-1] = end;
    return linspaced;
}


bool Utility::sameX(QVector<QPointF> points) //vraca true ako vector sadrzi tocke s istom x vrijednosti
{
    if(!points.empty())
        for(auto i = points.begin(); i != points.end(); ++i)
            for(auto j = i + 1; j != points.end(); ++j)
            {
                if(compareDoubles(i->x(), j->x()))
                    return true;
            }
    return false;
}

bool Utility::isUndefined(QPointF point)
{
    if(compareDoubles(point.x(), std::numeric_limits<double>::epsilon()) && compareDoubles(point.y(), std::numeric_limits<double>::epsilon()))
        return true;
    return false;
}
