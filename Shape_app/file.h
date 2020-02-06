#ifndef FILE_H
#define FILE_H

#include <QWidget>
#include <QTextStream>
#include "utility.h"

namespace Ui {
class File;
}

class File : public QWidget
{
    Q_OBJECT

public:
    explicit File(QString name_, QString color_, QWidget *parent = nullptr);
    ~File();    
    QString name;
    QString color;
    QVector<QPointF> points;
    QVector<QPointF> spline_points;

    QString generatePoints(QTextStream* in);
    void generateSplinePoints(double xStart, double xEnd);

signals:
    void deleteFileSignal(File *file);
private slots:
    void on_deleteFile_clicked();

private:
    Ui::File *ui;
};

#endif // FILE_H
