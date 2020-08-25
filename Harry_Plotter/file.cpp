#include "file.h"
#include "ui_file.h"
#include "spline.h"


File::File(QString name_, QString color_,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
    color = color_;
    ui->fileLabel->setStyleSheet("color: "+ color);
    ui->fileLabel->setText(name_);
    name = name_;


}

File::~File()
{
    delete ui;
}

void File::generateSplinePoints(double xStart, double xEnd)
{
    std::vector<double> X, Y;
    tk::spline s;

    spline_points.clear();
    if(points.empty())
        return;
    for(auto i = points.begin(); i != points.end(); ++i)
    {
        X.push_back(i->x());
        Y.push_back(i->y());
    }

    s.set_points(X,Y);
    QVector<double> x = Utility::linspace(xStart, xEnd, 1000);

    for(auto i = x.begin(); i != x.end(); ++i)
        spline_points.push_back(QPointF(*i,s(*i)));

    X.clear();
    Y.clear();
}


QString File::generatePoints(QTextStream* in)
{
    QVector<QPointF> points_;
    while (!in->atEnd())
    {
       QString line = in->readLine();
       QStringList coordinates = line.split(",", QString::SkipEmptyParts);
       if(coordinates.count() == 2)
       {
       bool checkX, checkY;
       double x = coordinates.at(0).trimmed().toDouble(&checkX);
       double y = coordinates.at(1).trimmed().toDouble(&checkY);
       if(checkX && checkY)
           points_.push_back(QPointF(x,y));
       }
    }

    if(points_.size() < 3)
    {
        ui->fileLabel->setStyleSheet("border: 2px solid #850000;\ncolor: "+ color);
        return "File \"" + name + "\" does not contain at least three correctly specified points.\n\nPoints from this file will not be plotted.";
    }

    if(Utility::sameX(points_)) //provjera sadrzi li file tocke s istom x vrijednosti
    {
        ui->fileLabel->setStyleSheet("border: 2px solid #850000;\ncolor: "+ color);
        return "File \"" + name + "\" contains points with same x value.\n\nPoints from this file will not be plotted.";
    }
    points = points_;

    return "";
}

void File::on_deleteFile_clicked()
{
   emit deleteFileSignal(this);
}

