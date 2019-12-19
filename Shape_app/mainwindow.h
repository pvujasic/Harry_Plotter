#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QFont>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <math.h>
#include <vector>
#include <tuple>

#include "coordinatesystem.h"
#include "point.h"
#include "connectingline.h"


using namespace std;

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

    void on_checkBox_stateChanged(int checked);


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    vector<QPointF> points;
    tuple<double, double, double, double> system_Info;
    int type;
    QList<connectingLine*> lines;

    void createLines();
    void deleteLines();
};
#endif // MAINWINDOW_H
