#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <tuple>

#include "ui_mainwindow.h"
#include "utility.h"
#include "colormanager.h"

class Function;
class File;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const static int x1 = 70; //gornji lijevi rub koordinatnog sustava
    const static int y1 = 50;
    const static int x2 = 50; //donji desni rub (odnosno scene->width()-x2, scene->height()-y2)
    const static int y2 = 50;

private slots:
    void on_selectFile_clicked();

    void on_gridBox_stateChanged(int arg1);

    void on_addFunction_clicked();

    void on_resetButton_clicked();

    void on_magicButton_clicked();

    void on_styleBox_currentIndexChanged(int index);

    void on_xFrom_valueChanged(double d);

    void on_xTo_valueChanged(double d);

    void on_yFrom_valueChanged(double arg1);

    void on_yTo_valueChanged(double arg1);

    void on_pointsNumber_valueChanged(int arg1);

    void  deleteFunction(Function *function);

    void deleteFile(File *file);

    void plot(bool automatic);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    std::tuple<double, double, double, double> system_Info; //informacije o koordinatnom sustavu koje sluze za iscrtavanje linija i tocaka
    QGraphicsItemGroup* grid;
    bool changedProgramatically; //kako bismo znali je li range promijenjen programski, u tom slucaju se ne zove funkcija plot
    QVector<Function*> functions;
    QVector<File*> files;
    ColorManager colorManager;


    QPointF transform(QPointF point);
    void createLines();
    void createPoints();
    void yBoundaries(double* yStart, double* yEnd, double xStart, double xEnd);
    bool pointInSystem(QPointF point);
};
#endif // MAINWINDOW_H
