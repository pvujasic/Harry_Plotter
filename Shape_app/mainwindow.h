#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <vector>
#include <tuple>

#include "ui_mainwindow.h"

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

    void on_x_from_valueChanged(double d);

    void on_x_to_valueChanged(double d);

    void on_y_from_valueChanged(double arg1);

    void on_y_to_valueChanged(double arg1);

    void on_pointsNumber_valueChanged(int arg1);

    void on_deleteFiles_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    std::vector<QPointF> filePoints[5]; //niz od 5 vectora tocaka pomocu kojih se iscrtavaju funkcije
    std::vector<QPointF> splinePoints[5]; //svaki vector sadrzi tocke potrebne za iscrtavanje kubicnog splinea za tocke iz datoteke
    std::vector<QPointF> functionPoints[5]; //tocke iz datoteka
    std::tuple<double, double, double, double> system_Info; //informacije o koordinatnom sustavu koje sluze za iscrtavanje linija i tocaka
    QGraphicsItemGroup* grid;
    std::vector<QLineEdit*> functionEdits; //tijekom izvodenja programa, dinamicki se kreiraju QLineEditi (za upisivanje funkcija) koje pamtimo u ovom vectoru
    std::vector<QLabel*> fileLabels; //labele koje sadrze imena odabranih datoteka
    std::vector<QCheckBox*> fileBoxes; //check boxovi koji omogucuju brisanje datoteka
    bool changedProgramatically; //kako bismo znali je li range promijenjen programski, u tom slucaju se ne zove funkcija plot

    QPointF transform(QPointF point);
    void createLines(std::vector<QPointF> points[5], bool type);
    void createPoints();
    void clearPoints();
    void yBoundaries(double* yStart, double* yEnd, double xStart, double xEnd);
    bool pointInSystem(QPointF point);
    void cubicSpline(double xStart, double xEnd);

    void plot(bool automatic);
};
#endif // MAINWINDOW_H
