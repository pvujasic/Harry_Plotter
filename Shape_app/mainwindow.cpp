#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectingline.h"
#include "coordinatesystem.h"
#include "point.h"
#include "function.h"
#include "file.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>


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
    scene->setSceneRect(0, 0, width, height);
    ui->graphicsView->setFixedSize(width+2*ui->graphicsView->frameWidth(), height+2*ui->graphicsView->frameWidth());
    this->setFixedSize(QSize(1062, 800));

    grid = new QGraphicsItemGroup();
    changedProgramatically = false;
    plot(false);
    ui->warningLabel->setText("Get started!");



}

MainWindow::~MainWindow()
{
    delete ui;
}

QPointF MainWindow::transform(QPointF point) //transformira tocku u onu koja ce se iscrtati na ekranu (u ovisnosti o koordinatnom sustavu)
{
    auto[xStart, yStart, xStep, yStep] = system_Info;
    return QPointF(x1 + (point.x()-xStart)*xStep, scene->height()-y2 - (point.y()-yStart)*yStep);
}



bool operator<(QPointF a, QPointF b) //kako bismo mogli sortirati vector tocaka
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

void MainWindow::on_selectFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
    if(fileName.isEmpty())
        return;

    QFile file_(fileName);
    file_.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file_);
    QVector<QPointF> points;
    if(fileName.contains("/"))
        fileName.remove(0, fileName.lastIndexOf("/")+1);
    File* file = new File(fileName, colorManager.getFileColor());
    files.append(file);
    QString message = file->generatePoints(&in);
    std::sort(file->points.begin(), file->points.end());
    file_.close();
    ui->fileLayout->addWidget(file);
    connect(file, &File::deleteFileSignal, this, &MainWindow::deleteFile);

    if(message != "")
        ui->warningLabel->setText(message);
    else
        plot(true);

    if(int(files.size()) == 5)
        ui->selectFile->setEnabled(false);
}


void MainWindow::yBoundaries(double* yStart, double* yEnd, double xStart, double xEnd) //za automatsko racunanje y range-a,
                                                                                       //traze se max i min tocaka svih funkcija i datoteka
{
    QVector<double> Y;

    if(!files.empty())
    {
        for (auto i = files.begin(); i != files.end(); ++i)
        {
            if((*i)->points.empty())
                continue;
            for (auto j = (*i)->points.begin(); j != (*i)->points.end(); ++j)
            {
                if(Utility::isUndefined(*j))
                    continue;
                if(j->x() >= xStart && j->x() <= xEnd)
                    Y.push_back(j->y());
            }
        }
    }

    if(!functions.empty())
    {
        for (auto i = functions.begin(); i != functions.end(); ++i)
        {
            if((*i)->points.empty())
                continue;
            for (auto j = (*i)->points.begin(); j != (*i)->points.end(); ++j)
            {
                if(Utility::isUndefined(*j))
                    continue;
                if(j->x() >= xStart && j->x() <= xEnd)
                    Y.push_back(j->y());
            }
        }
    }

    if(Y.empty())
        *yStart = *yEnd = 0;
    else
    {
        std::sort(Y.begin(), Y.end());
        *yStart = Y.front();
        *yEnd = Y.back();
    }

    if(Utility::compareDoubles(*yStart, *yEnd)) //konstantna funkcija ili nema tocaka
    {
        *yStart -= 3;
        *yEnd += 3;
    }
}

void MainWindow::plot(bool automatic) //najvaznija funkcija, poziva se svaki put prilikom crtanja na sceni
                                      //argument automatic - true ako se x i y range racunaju automatski, inace false
{
    scene->clear();
    ui->warningLabel->setText("");
    QString warningText = "";
    double xStart, xEnd, yStart, yEnd;

    xStart = double(ui->xFrom->value());
    xEnd = double(ui->xTo->value());

    if(xStart >= xEnd)
    {
        ui->warningLabel->setText("Incorrect x range!");
        return;
    }

    if(automatic)  //ako se x range racuna automatski, uzimaju se u obzir x koordinate tocaka iz datoteka i trenutni x range te se stavljaju maksimalne(minimalne) vrijednosti
    {
        double min = xStart, max = xEnd;
        if(!files.empty())
        {
            for(auto i = files.begin(); i != files.end(); ++i)
            {
                if(!(*i)->points.empty())
                {
                    if((*i)->points.front().x() < min)
                        min = (*i)->points.front().x();
                    if((*i)->points.back().x() > max)
                        max = (*i)->points.back().x();
                }
            }
        }
        xStart = min;
        xEnd = max;
    }

    if(!functions.empty())
        for(auto i = functions.begin(); i != functions.end(); ++i)
            warningText += (*i)->generatePoints(xStart, xEnd, ui->pointsNumber->value());

    if(ui->styleBox->currentIndex() == 2)
        if(!files.empty())
            for(auto i = files.begin(); i != files.end(); ++i)
                (*i)->generateSplinePoints(xStart, xEnd);


    ui->warningLabel->setText(warningText);

    if(automatic)
    {
        yBoundaries(&yStart, &yEnd, xStart, xEnd);

        changedProgramatically = true;
        ui->yFrom->setValue(yStart);
        changedProgramatically = true;
        ui->yTo->setValue(yEnd);

        changedProgramatically = true;
        ui->xFrom->setValue(xStart);
        changedProgramatically = true;
        ui->xTo->setValue(xEnd);
    }
    else
    {
        yStart = ui->yFrom->value();
        yEnd = ui->yTo->value();
    }

    yEnd += 0.02*(yEnd-yStart); //kod postavljanja koordinatnog sustava saljemo malo manje/vece vrijednosti kako bi se izbjeglo iscrtavanje uz sam rub sustava
    yStart -= 0.02*(yEnd-yStart);
    xEnd += 0.02*(xEnd-xStart);
    xStart -= 0.02*(xEnd-xStart);

    coordinateSystem* system = new coordinateSystem(scene);
    auto[system_Info_, grid_] = system->init(scene, xStart, xEnd, yStart, yEnd);
    system_Info = system_Info_;
    grid = grid_;


    createPoints();
    createLines();

    if(!ui->gridBox->isChecked())
       grid->hide();
}


void MainWindow::on_magicButton_clicked()
{
    bool flag = false;
    double min = -3;
    double max = 3;
    if(!files.empty())
    {
        for(auto i = files.begin(); i != files.end(); ++i)
        {
            if(!(*i)->points.empty())
            {
                if(!flag)
                {
                    min = max = (*i)->points.front().x();
                    flag = true;
                }
                if((*i)->points.front().x() < min)
                    min = (*i)->points.front().x();
                if((*i)->points.back().x() > max)
                    max = (*i)->points.back().x();
            }
        }
    }

    changedProgramatically = true;
    ui->xFrom->setValue(min);
    changedProgramatically = true;
    ui->xTo->setValue(max);
    plot(true); //automatski se racuna range

    //for(auto i = functionPoints[0].begin(); i != functionPoints[0].end(); ++i) //kreiranje datoteka
        //qDebug() << QString::number(i->x()) + ", " + QString::number(i->y());
    //qDebug() << "------------------";
}





void MainWindow::on_styleBox_currentIndexChanged(int index)
{
    if(!files.empty())
        plot(false);
}



bool MainWindow::pointInSystem(QPointF point) //kako tocke i linije ne bi prelazile rubove koordinatnog sustava (mogu biti samo malo vece od range-a i nikad ne smiju prelaziti rubove)
{
    double multiplier = (ui->yFrom->value() > 0)? 0.9:1.1;
    if(point.x() < ui->xFrom->value() || point.x() > ui->xTo->value() || point.y() < ui->yFrom->value()*multiplier || point.y() > ui->yTo->value()*1.1)
        return false;
    point = transform(point);
    if(point.x() < x1 || point.x() > scene->width()-x2 || point.y() < y1 || point.y() > scene->height()-y2)
        return false;

    return true;
}

void MainWindow::createPoints() //na scenu se dodaju tocke iz datoteka
{
    if(!files.empty())
    {
        for(auto i = files.begin(); i != files.end(); ++i)
        {
            if(!(*i)->points.empty())
            {
                for (auto j = (*i)->points.begin(); j != (*i)->points.end(); ++j)
                {
                    if(pointInSystem(*j))
                    {
                        Point* point = new Point(*j, transform(*j), (*i)->color, scene);
                        scene->addItem(point);
                    }
                }
            }
        }
     }
}


void MainWindow::createLines() //na scenu se dodaju linije koje cine funkcije
{
    if(!functions.empty())
    {
        for(auto i = functions.begin(); i != functions.end(); ++i)
        {
            if(!(*i)->points.empty())
            {
                for (auto j = (*i)->points.begin(); j != ((*i)->points.end() - 1); ++j)
                {
                    if(Utility::isUndefined(*j) || Utility::isUndefined(*(j+1)))
                        continue;
                    if(pointInSystem(*j) && pointInSystem(*(j+1)))
                    {
                        connectingLine* line = new connectingLine(transform(*j), transform(*(j+1)), (*i)->color, (*i)->name, scene);
                        scene->addItem(line);
                    }
                }
            }
        }
    }

    if(!files.empty())
    {
        if(ui->styleBox->currentIndex() == 1)
        {
            for(auto i = files.begin(); i != files.end(); ++i)
            {
                if(!(*i)->points.empty())
                {
                    for (auto j = (*i)->points.begin(); j != ((*i)->points.end() - 1); ++j)
                    {
                        if(pointInSystem(*j) && pointInSystem(*(j+1)))
                        {
                            connectingLine* line = new connectingLine(transform(*j), transform(*(j+1)), (*i)->color, (*i)->name, scene);
                            scene->addItem(line);
                        }
                    }
                }
            }
        }

        else if(ui->styleBox->currentIndex() == 2)
        {
            for(auto i = files.begin(); i != files.end(); ++i)
            {
                if(!(*i)->spline_points.empty())
                {
                    for (auto j = (*i)->spline_points.begin(); j != ((*i)->spline_points.end() - 1); ++j)
                    {
                        if(pointInSystem(*j) && pointInSystem(*(j+1)))
                        {
                            connectingLine* line = new connectingLine(transform(*j), transform(*(j+1)), (*i)->color, (*i)->name, scene);
                            scene->addItem(line);
                        }
                    }
                }
            }
        }
    }
}



void MainWindow::on_gridBox_stateChanged(int checked)
{
    if(checked)
        grid->show();
    else
        grid->hide();
}

void MainWindow::on_addFunction_clicked()
{
    Function* function = new Function(colorManager.getFunctionColor());
    functions.append(function);
    ui->functionLayout->addWidget(function);

    connect(function, &Function::deleteFunctionSignal, this, &MainWindow::deleteFunction);
    connect(function, &Function::plotSignal, this, &MainWindow::plot);

    if(int(functions.size()) == 5)
        ui->addFunction->setEnabled(false);
}




void MainWindow::on_resetButton_clicked() //defaultne postavke i onemogucavanje odgovarajucih gumba
{
    for(auto i = files.begin(); i != files.end(); ++i)
        delete *i;
    for(auto i = functions.begin(); i != functions.end(); ++i)
        delete *i;
    files.clear();
    functions.clear();
    colorManager.reset();


    ui->warningLabel->setText("");
    changedProgramatically = true;
    ui->xFrom->setValue(-3);
    changedProgramatically = true;
    ui->xTo->setValue(3);
    changedProgramatically = true;
    ui->yFrom->setValue(-3);
    changedProgramatically = true;
    ui->yTo->setValue(3);
    ui->pointsNumber->setValue(101);
    ui->styleBox->setCurrentIndex(0);
    ui->gridBox->setCheckState(Qt::CheckState(false));
    ui->addFunction->setEnabled(true);

    plot(false);
}

void MainWindow::on_xFrom_valueChanged(double d)
{
    if(changedProgramatically)
    {
        changedProgramatically = false;
        return;
    }
    if(ui->xTo->value() - ui->xFrom->value() <= 0)
    {
        ui->warningLabel->setText("Incorrect x range!");
        return;
    }

    plot(false);
}

void MainWindow::on_xTo_valueChanged(double d)
{
    if(changedProgramatically)
    {
        changedProgramatically = false;
        return;
    }
    if(ui->xTo->value() - ui->xFrom->value() <= 0)
    {
        ui->warningLabel->setText("Incorrect x range!");
        return;
    }

    plot(false);
}

void MainWindow::on_yFrom_valueChanged(double arg1)
{
    if(changedProgramatically)
    {
        changedProgramatically = false;
        return;
    }
    if(ui->yTo->value() - ui->yFrom->value() <= 0)
    {
        ui->warningLabel->setText("Incorrect y range!");
        return;
    }

    plot(false);
}

void MainWindow::on_yTo_valueChanged(double arg1)
{
    if(changedProgramatically)
    {
        changedProgramatically = false;
        return;
    }
    if(ui->yTo->value() - ui->yFrom->value() <= 0)
    {
        ui->warningLabel->setText("Incorrect y range!");
        return;
    }

    plot(false);
}

void MainWindow::on_pointsNumber_valueChanged(int arg1)
{
    if(!functions.empty())
        plot(true);
}

void MainWindow::deleteFunction(Function *function)
{
    functions.removeOne(function);
    ui->functionLayout->removeWidget(function);
    function->setParent(nullptr);
    colorManager.releaseFunctionColor(function->color);
    delete function;
    ui->addFunction->setEnabled(true);
    plot(false);
}

void MainWindow::deleteFile(File *file)
{
    files.removeOne(file);
    ui->fileLayout->removeWidget(file);
    file->setParent(nullptr);
    colorManager.releaseFileColor(file->color);
    delete file;
    ui->selectFile->setEnabled(true);
    plot(false);
}

