#ifndef COLORMANAGER_H
#define COLORMANAGER_H
#include <QString>


class ColorManager
{
public:
    ColorManager();

    QString getFileColor();
    QString getFunctionColor();
    void releaseFileColor(QString color);
    void releaseFunctionColor(QString color);
    void reset();

private:
    bool fileColors[5];
    bool functionColors[5];
};

#endif // COLORMANAGER_H
