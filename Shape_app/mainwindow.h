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

#include "ui_mainwindow.h" //jel to ok

class connectingLine;


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

    void on_add_function_clicked();

    void on_delete_function_clicked();

    void on_resetButton_clicked();

    void on_drawButton_clicked();

    void on_style_comboBox_currentIndexChanged(int index);

    void on_functionEdit1_textEdited();

    void on_x_from_valueChanged(double d);

    void on_x_to_valueChanged(double d);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    std::vector<QPointF> filePoints[5]; //niz od 5 vectora (jer je moguce iscrtati max. 5 fja - u slucaju iscrtavanja iz datoteke samo prvi vector sadrzi tocke)
    std::vector<QPointF> splinePoints[5];
    std::vector<QPointF> functionPoints[5];
    std::tuple<double, double, double, double> system_Info; //informacije o koordinatnom sustavu koje sluze za iscrtavanje linija i tocaka
    QGraphicsItemGroup* grid;
    std::vector<QLineEdit*> functionEdits;
    std::vector<QLabel*> fileLabels;
    std::vector<QCheckBox*> fileBoxes;

    double transformX(double x);
    double transformY(double y);
    void createLines();
    void createPoints();
    void disableButtons();
    int firstEmpty(bool type);
    int numberElements(bool type);
    void clearPoints();
    void yBoundaries(double* yStart, double* yEnd, double xStart, double xEnd);

    void plot(QPointF xRange, QPointF yRange);
};
#endif // MAINWINDOW_H
