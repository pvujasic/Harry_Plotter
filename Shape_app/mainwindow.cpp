#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectingline.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    int width = ui->graphicsView->width();
    int height =ui->graphicsView->height();
    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height()); //ili tu samo - 2*frameWidth..
    ui->graphicsView->setFixedSize(width+2*ui->graphicsView->frameWidth(), height+2*ui->graphicsView->frameWidth());
    type = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

tuple<double, double, double, double> findBoundaries(vector<QPointF> points)
{
    double xStart, xEnd, yStart, yEnd;
    auto i = points.begin();
    xStart = xEnd = i->x();
    yStart = yEnd = i->y();

    while(i != points.end())
    {
        if(i->x() < xStart)
            xStart = i->x();
        if(i->x() > xEnd)
            xEnd = i->x();
        if(i->y() < yStart)
            yStart = i->y();
        if(i->y() > yEnd)
            yEnd = i->y();
        ++i;
    }
    return make_tuple(xStart, xEnd, yStart, yEnd);
}


void MainWindow::on_selectFile_clicked()
{
    type = 1;
    scene->clear();
    points.clear();
    lines.clear();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
    if(fileName.isEmpty()){
        return;
    }
    QFile file(fileName); // "/home/paula/Diplomski"
    file.open(QIODevice::ReadOnly | QIODevice::Text);   

    QTextStream in(&file);
    while (!in.atEnd())
    {
       QString line = in.readLine();
       QStringList coordinates = line.split(",", QString::SkipEmptyParts);
       if(coordinates.count() == 2)
       {
       bool checkX, checkY;
       double x = coordinates.at(0).trimmed().toDouble(&checkX);
       double y = coordinates.at(1).trimmed().toDouble(&checkY);
       if(checkX && checkY)
           points.push_back(QPointF(x,y));
       }
    }
    file.close();
    coordinateSystem* system = new coordinateSystem(scene);

    tuple<double, double, double, double> boundaries = findBoundaries(points);
    if(get<1>(boundaries) - get<0>(boundaries) <= 0)
        return;
    system_Info = system->init(scene, get<0>(boundaries), get<1>(boundaries), get<2>(boundaries), get<3>(boundaries));

    for (auto i = points.begin(); i != points.end(); ++i)
    {
        Point* point = new Point();
        point->initPoint(scene, i->x(), i->y(), system_Info);
    }

    if(ui->checkBox->isChecked())
       createLines();
}

vector<double> linspace(double start, double end, int num)
{
  vector<double> linspaced;
  double delta = (end - start)/(num - 1);

  for(int i = 0; i < num-1; ++i)
    {
      linspaced.push_back(start + delta * i);
    }
  linspaced.push_back(end);
  return linspaced;
}

bool compareDoubles(double a, double b)
{
   double diff = a - b;
   return (diff < numeric_limits<double>::epsilon()) && (diff > -numeric_limits<double>::epsilon());
}

void MainWindow::on_pushButton_clicked()
{
    type = 2;
    scene->clear();
    points.clear();
    lines.clear();

    double xStart = double(ui->doubleSpinBox->value());
    double xEnd = double(ui->doubleSpinBox_2->value());

    if(xEnd - xStart <= 0)
        return;

    QString function = ui->lineEdit->text();
    double yStart, yEnd;
    yStart = yEnd = sin(xStart);

    vector<double> x = linspace(xStart, xEnd, 1000);
    for (auto i = x.begin(); i != x.end(); ++i)
    {
        double f_x = (*i)*(*i)*(*i);
        if(f_x < yStart)
            yStart = f_x;
        if(f_x > yEnd)
            yEnd = f_x;
        points.push_back(QPointF(*i, f_x));
    }

    if(compareDoubles(yStart, yEnd)) //konstantna funkcija
    {
        yStart -= 3;
        yEnd += 3;
    }

    coordinateSystem* system = new coordinateSystem(scene);
    system_Info = system->init(scene, xStart, xEnd, yStart, yEnd);

    createLines();
}


void MainWindow::on_checkBox_stateChanged(int checked)
{
    if(type == 1)
    {
    if(checked)
       createLines();
    else
        deleteLines();
    }
}

bool operator < (QPointF a, QPointF b)
{
    if(a.x() < b.x())
        return true;
    else if(a.x() > b.x())
        return false;
    else
    {
        if(a.y() < b.y())
            return true;
        else
            return false;
    }
}

void MainWindow::createLines()
{
    sort(points.begin(), points.end());
    for (auto i = points.begin(); i != (points.end() - 1); ++i)
    {
        connectingLine* line = new connectingLine();
        line->initLine(scene, i->x(), i->y(), (i+1)->x(), (i+1)->y(), system_Info);
        lines.push_back(line);
    }
}

void MainWindow::deleteLines()
{
    for(int i = 0; i < lines.size(); ++i)
    {
        scene->removeItem(lines.at(i));
        delete lines.at(i);
    }
    lines.clear();
}


