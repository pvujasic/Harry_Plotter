#ifndef UTILITY_H
#define UTILITY_H
#include <QVector>
#include <QPointF>

class Utility
{
public:
    Utility();

    static bool compareDoubles(double a, double b);
    static QVector<double> linspace(double start, double end, int num);
    static bool sameX(QVector<QPointF> points);
    static bool isUndefined(QPointF point);
};

#endif // UTILITY_H
