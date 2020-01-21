#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectingline.h"
#include "coordinatesystem.h"
#include "point.h"
#include "fparser.hh"
#include "spline.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

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
    scene->setSceneRect(0, 0, width, height);
    ui->graphicsView->setFixedSize(width+2*ui->graphicsView->frameWidth(), height+2*ui->graphicsView->frameWidth());
    this->setFixedSize(QSize(1062, 800));

    QGraphicsTextItem* startText = new QGraphicsTextItem();
    startText->setPlainText("Get started!");
    startText->setDefaultTextColor(Qt::gray);
    startText->setPos(scene->width()/2 - startText->boundingRect().width()/2, scene->height()/2 - startText->boundingRect().height()/2);
    scene->addItem(startText);

    functionEdits.push_back(ui->functionEdit1);
    grid = new QGraphicsItemGroup();
    changedProgramatically = false;
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

bool compareDoubles(double a, double b)
{
   double diff = a - b;
   return (diff < numeric_limits<double>::epsilon()) && (diff > -numeric_limits<double>::epsilon());
}

bool sameX(vector<QPointF> points) //vraca true ako vector sadrzi tocke s istom x vrijednosti
{
    sort(points.begin(), points.end());
    if(!points.empty())
        for(auto i = points.begin(); i != points.end() - 1; ++i)
        {
            if(compareDoubles(i->x(), (i+1)->x()))
                return true;
        }
    return false;
}

QString selectColor(int colorNumber) //prvih 5 boja je za funkcije, drugih 5 za datoteke
{
    switch(colorNumber)
    {
        case(0):
            return QString("#ffc400");
        case(1):
            return QString("#ff7f2e");
        case(2):
            return QString("#ff2b8f");
        case(3):
            return QString("#5993ff");
        case(4):
            return QString("#32f0a3");
        case(5):
            return QString("#7ddbb5");
        case(6):
            return QString("#829dd1");
        case(7):
            return QString("#db72a4");
        case(8):
            return QString("#e69460");
        default:
            return QString("#e3c666");
    }
}

int firstEmpty(vector<QLabel*> fileLabels) //vraca redni broj prvog slobodnog mjesta u vectoru fileLabels
{
    if(fileLabels.empty())
        return 0;
    int n = 0;
    for(auto i = fileLabels.begin(); i != fileLabels.end(); ++i)
    {
        if(!(*i))
            return n;
        ++n;
    }
    return n;
}

int numberElements(vector<QLabel*> fileLabels) //vraca broj datoteka
{
    int n = 0;
    if(fileLabels.empty())
        return 0;
    for(auto i = fileLabels.begin(); i != fileLabels.end(); ++i)
        if(*i)
            ++n;
    return n;
}

vector<double> linspace(double start, double end, int num) //po uzoru na pythonovu fju linspace, vraca vector jednoliko rasporedenih brojeva u zadanom intervalu
{
    vector<double> linspaced(num);
    double delta = (end - start)/(num - 1);

    for(int i = 0; i < num-1; ++i)
      {
        linspaced[i] = start + delta * i;
      }

    linspaced[num-1] = end;
    return linspaced;
}

void MainWindow::cubicSpline(double xStart, double xEnd) //u niz splinePoints na odgovarajuca mjesta stavlja vectore sa vrijednostima kubicnog splinea

{
    vector<double> X, Y;
    tk::spline s;


    for(int n = 0; n < 5; ++n)
    {
        splinePoints[n].clear();
        if(filePoints[n].empty())
            continue;
        for(auto i = filePoints[n].begin(); i != filePoints[n].end(); ++i)
        {
            X.push_back(i->x());
            Y.push_back(i->y());
        }

        s.set_points(X,Y);
        vector<double> x = linspace(xStart, xEnd, 1000);

        for(auto i = x.begin(); i != x.end(); ++i)
            splinePoints[n].push_back(QPointF(*i,s(*i)));

        X.clear();
        Y.clear();
    }
}

void MainWindow::on_selectFile_clicked() //pritiskom gumba Select file u filePoints se na odgovarajuce mjesto sprema vector tocaka iz datoteke
{
    ui->warningLabel->setText("");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)")); //"/home/paula/shape-app"
    if(fileName.isEmpty()){
        return;
    }

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    int position = firstEmpty(fileLabels);
    int fileNumber = numberElements(fileLabels);

    vector<QPointF> points;
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

    QString color = selectColor(int(position + 5));

    if(fileName.contains("/"))
        fileName.remove(0,fileName.lastIndexOf("/")+1);

    QLabel* fileLabel = new QLabel(fileName);
    fileLabel->setStyleSheet("color: "+ color);

    QCheckBox* fileBox = new QCheckBox("");

    ui->formLayout_2->insertRow(fileNumber,fileLabel,fileBox);

    if(fileNumber != int(fileLabels.size()))
    {
    fileLabels[position] = fileLabel;
    fileBoxes[position] = fileBox;
    }
    else
    {
        fileLabels.push_back(fileLabel);
        fileBoxes.push_back(fileBox);
    }

    if(int(fileNumber == 5))
        ui->selectFile->setEnabled(false);

    if(points.size() < 3)
    {
        ui->warningLabel->setText("File does not contain at least three correctly specified points.\n\nPoints from this file won't be plotted.");
        fileLabels[position]->setStyleSheet("border: 1px solid #850000;\ncolor: "+ color);
        return;
    }

    if(sameX(points)) //provjera sadrzi li file tocke s istom x vrijednosti
    {
        ui->warningLabel->setText("File contains points with same x value.\n\nPoints from this file won't be plotted.");
        fileLabels[position]->setStyleSheet("border: 1px solid #850000;\ncolor: "+ color);
        return;
    }

    sort(points.begin(), points.end());
    filePoints[position] = points;

    if(numberElements(fileLabels) == 5)
        ui->selectFile->setEnabled(false);
}

bool isUndefined(QPointF point) //provjerava je li tocka definirana (npr. ako za x vrijednost funkcija nije definirana, tocka se sprema kao (epsilon, epsilon)
{
    if(compareDoubles(point.x(), numeric_limits<double>::epsilon()) && compareDoubles(point.y(), numeric_limits<double>::epsilon()))
        return true;
    return false;
}

void pushPoints(vector<QPointF> points[5], vector<double>* Y, double xStart, double xEnd) //sluzi za funkciju yBoundaries, u vector Y se stavljaju y koordinate
                                                                                          //svih vectora tocaka, ali samo one za koje je x izmedu xStart i xEnd
{
    for(int n = 0; n < 5; ++n)
    {
        if(points[n].empty())
            continue;
        for (auto i = points[n].begin(); i != points[n].end(); ++i)
        {
            if(isUndefined(*i))
                continue;
            if(i->x() >= xStart && i->x() <= xEnd)
                Y->push_back(i->y());
        }
    }
}

void MainWindow::yBoundaries(double* yStart, double* yEnd, double xStart, double xEnd) //za automatsko racunanje y range-a,
                                                                                       //traze se max i min tocaka svih funkcija i datoteka
{
    vector<double> Y;
    pushPoints(functionPoints, &Y, xStart, xEnd);
    pushPoints(filePoints, &Y, xStart, xEnd);
    //if(ui->style_comboBox->currentIndex() == 2)
        //pushPoints(splinePoints, &Y, xStart, xEnd);

    if(Y.empty())
        *yStart = *yEnd = 0;
    else
    {
        sort(Y.begin(), Y.end());
        *yStart = Y.front();
        *yEnd = Y.back();
    }

    if(compareDoubles(*yStart, *yEnd)) //konstantna funkcija ili nema tocaka
    {
        *yStart -= 3;
        *yEnd += 3;
    }
}

void MainWindow::plot(bool automatic) //najvaznija funkcija, poziva se svaki put prilikom crtanja na sceni
                                      //argument automatic - true ako se x i y range racunaju automatski, inace false
{
    ui->warningLabel->setText("");
    QString warningText = "";
    double xStart, xEnd, yStart, yEnd;

    xStart = double(ui->x_from->value());
    xEnd = double(ui->x_to->value());

    if(xStart >= xEnd)
    {
        ui->warningLabel->setText("Incorrect x range!");
        return;
    }

    if(automatic)  //ako se x range racuna automatski, uzimaju se u obzir x koordinate tocaka iz datoteka i trenutni x range te se stavljaju maksimalne(minimalne) vrijednosti
    {
        double min = xStart, max = xEnd;
        for(int i = 0; i < 5; ++i)
        {
            if(!filePoints[i].empty())
            {
                if(filePoints[i].front().x() < min) //filePoints su uvijek sortirane
                    min = filePoints[i].front().x();
                if(filePoints[i].back().x() > max)
                    max = filePoints[i].back().x();
            }
        }
        xStart = min;
        xEnd = max;
    }

    if(ui->style_comboBox->currentIndex() == 2)
        cubicSpline(xStart, xEnd);

    FunctionParser fparser;
    fparser.AddConstant("pi", 3.14159265358979323846);
    fparser.AddConstant("e", 2.71828182845904523536);

    double value[1]; //funkcija Eval() kod FunctionParsera prima pointer na niz (buduci da iscrtavamo samo fje jedne varijable, taj niz uvijek ima jedan element)

    scene->clear();
    for(int i = 0; i < 5; ++i)
        functionPoints[i].clear();

    value[0] = xStart;

    int n = -1;
    for(auto i = functionEdits.begin(); i != functionEdits.end(); ++i) //u niz vectora functionPoints dodajemo tocke potrebne za iscrtavanje funkcija
    {
        n++;
        if (fparser.Parse((*i)->text().toStdString(), "x") != -1)
        {
            if((*i)->text() != "")
                warningText += "Incorrectly specified function: f(x) = " + (*i)->text() + "\n\n";
            continue;
        }
        QString function = (*i)->text();

        fparser.Parse(function.toStdString(), "x");
        vector<double> x = linspace(xStart, xEnd, ui->pointsNumber->value());
        for(auto j = x.begin(); j != x.end(); ++j)
        {
            value[0] = *j;
            double f_x = fparser.Eval(value);
            if (!fparser.EvalError())
                functionPoints[n].push_back(QPointF(*j, f_x));
            else
            {
                functionPoints[n].push_back(QPointF(numeric_limits<double>::epsilon(),numeric_limits<double>::epsilon()));
                if(!warningText.contains("Function f(x) = " + (*i)->text() + " is not defined for the whole range."))
                    warningText += "Function f(x) = " + (*i)->text() + " is not defined for the whole range.\n\n";
            }
        }
    }

    ui->warningLabel->setText(warningText);

    if(automatic)
    {
        yBoundaries(&yStart, &yEnd, xStart, xEnd);

        changedProgramatically = true;
        ui->y_from->setValue(yStart);
        changedProgramatically = true;
        ui->y_to->setValue(yEnd);

        changedProgramatically = true;
        ui->x_from->setValue(xStart);
        changedProgramatically = true;
        ui->x_to->setValue(xEnd);
    }
    else
    {
        yStart = ui->y_from->value();
        yEnd = ui->y_to->value();
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
    createLines(functionPoints, 1);
    if(ui->style_comboBox->currentIndex() == 1)
        createLines(filePoints, 0);
    if(ui->style_comboBox->currentIndex() == 2)
        createLines(splinePoints, 0);

    if(!ui->gridBox->isChecked())
       grid->hide();

    ui->x_from->setEnabled(true);
    ui->x_to->setEnabled(true);
    ui->y_from->setEnabled(true);
    ui->y_to->setEnabled(true);
}


void MainWindow::on_drawButton_clicked()
{
    plot(true); //automatski se racuna range

    //for(auto i = functionPoints[0].begin(); i != functionPoints[0].end(); ++i) //kreiranje datoteka
        //qDebug() << QString::number(i->x()) + ", " + QString::number(i->y());
    //qDebug() << "------------------";
}

bool pointsEmpty(vector<QPointF> points[5]) //provjera je li svaki od 5 vectora tocaka prazan
{
    for(int i = 0; i < 5; ++i)
    {
        if(!points[i].empty())
            return false;
    }
    return true;
}

void MainWindow::on_style_comboBox_currentIndexChanged(int index)
{
    if(!pointsEmpty(filePoints))
        plot(false);
}


bool operator < (QPointF a, QPointF b) //kako bismo mogli sortirati vector tocaka
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

bool MainWindow::pointInSystem(QPointF point) //kako tocke i linije ne bi prelazile rubove koordinatnog sustava (mogu biti samo malo vece od range-a i nikad ne smiju prelaziti rubove)
{
    double multiplier = (ui->y_from->value() > 0)? 0.9:1.1;
    if(point.x() < ui->x_from->value() || point.x() > ui->x_to->value() || point.y() < ui->y_from->value()*multiplier || point.y() > ui->y_to->value()*1.1)
        return false;
    point = transform(point);
    if(point.x() < x1 || point.x() > scene->width()-x2 || point.y() < y1 || point.y() > scene->height()-y2)
        return false;

    return true;
}

void MainWindow::createPoints() //na scenu se dodaju tocke iz datoteka
{
    for(int n = 0; n < 5; ++n)
    {
        if(filePoints[n].empty())
            continue;

        for (auto i = filePoints[n].begin(); i != filePoints[n].end(); ++i)
        {
            if(pointInSystem(*i))
            {
                Point* point = new Point(*i, transform(*i), selectColor(n+5), scene);
                scene->addItem(point);
            }
        }
    }
}


void MainWindow::createLines(vector<QPointF> points[5], bool type) //na scenu se dodaju linije koje cine funkcije
                                                                   //type - 0 za datoteke, 1 za funkcije
{
    QString color;
    QString text;
    for (int n = 0; n < 5; ++n)
    {
        if(points[n].empty())
            continue;

        if(type)
        {
            color = selectColor(n);
            text = "f(x) = " + functionEdits[unsigned(n)]->text();
        }
        else
        {
            color = selectColor(n+5);
            text = fileLabels[unsigned(n)]->text();
        }

        for (auto i = points[n].begin(); i != (points[n].end() - 1); ++i)
        {
            if(isUndefined(*i) || isUndefined(*(i+1)))
                continue;
            if(pointInSystem(*i) && pointInSystem(*(i+1)))
            {
                connectingLine* line = new connectingLine(transform(*i), transform(*(i+1)), color, text, scene);
                scene->addItem(line);
            }
        }
    }
}

void MainWindow::clearPoints()
{
    for(int i = 0; i < 5; ++i)
    {
        filePoints[i].clear();
        splinePoints[i].clear();
        functionPoints[i].clear();
    }
}


void MainWindow::on_gridBox_stateChanged(int checked)
{
    if(checked)
        grid->show();
    else
        grid->hide();
}

void MainWindow::on_add_function_clicked()
{
    QString color = selectColor(int(functionEdits.size()));

    QLabel* functionLabel = new QLabel("f(x) =");
    functionLabel->setStyleSheet("color: "+ color);

    QLineEdit* functionEdit = new QLineEdit();
    functionEdit->setStyleSheet("color: "+ color+";\nbackground-color: #1C1C1C;");

    ui->formLayout->insertRow(int(functionEdits.size()),functionLabel,functionEdit);
    functionEdits.push_back(functionEdit);

    if(int(functionEdits.size()) == 5)
        ui->add_function->setEnabled(false);

    ui->delete_function->setEnabled(true);
}


void MainWindow::on_delete_function_clicked()
{
    functionEdits.pop_back();
    ui->formLayout->removeRow(int(functionEdits.size()));

    if(int(functionEdits.size()) == 1)
        ui->delete_function->setEnabled(false);

    ui->add_function->setEnabled(true);
}


void MainWindow::on_deleteFiles_clicked()
{
    int n = 0;
    QLabel* label;
    if(!fileBoxes.empty())
    {
        for(auto i = fileBoxes.begin(); i != fileBoxes.end(); ++i)
        {
            if(*i)
                if(fileBoxes[n]->isChecked())
                {
                    filePoints[n].clear();
                    splinePoints[n].clear();
                    label = fileLabels[n];
                    fileLabels[n] = nullptr;
                    fileBoxes[n] = nullptr;
                    ui->formLayout_2->removeRow(ui->formLayout_2->indexOf(label)/2);
                }
            ++n;
        }
    }
    if(numberElements(fileLabels) < 5)
        ui->selectFile->setEnabled(true);
}

void MainWindow::on_resetButton_clicked() //defaultne postavke i onemogucavanje odgovarajucih gumba
{
    for(int i = int(functionEdits.size())-1; i > 0; --i)
        ui->formLayout->removeRow(i);

    for(int i = numberElements(fileLabels)-1; i >= 0; --i)
        ui->formLayout_2->removeRow(i);

    functionEdits.clear();
    functionEdits.push_back(ui->functionEdit1);
    fileLabels.clear();
    fileBoxes.clear();
    clearPoints();

    ui->functionEdit1->setText("");
    ui->warningLabel->setText("");
    changedProgramatically = true;
    ui->x_from->setValue(-3);
    changedProgramatically = true;
    ui->x_to->setValue(3);
    changedProgramatically = true;
    ui->y_from->setValue(-3);
    changedProgramatically = true;
    ui->y_to->setValue(3);
    ui->pointsNumber->setValue(101);
    ui->style_comboBox->setCurrentIndex(0);
    ui->gridBox->setCheckState(Qt::CheckState(false));
    ui->delete_function->setEnabled(false);
    ui->add_function->setEnabled(true);

    plot(false);
}

void MainWindow::on_x_from_valueChanged(double d)
{
    if(changedProgramatically)
    {
        changedProgramatically = false;
        return;
    }
    if(ui->x_to->value() - ui->x_from->value() <= 0)
    {
        ui->warningLabel->setText("Incorrect x range!");
        return;
    }

    plot(false);
}

void MainWindow::on_x_to_valueChanged(double d)
{
    if(changedProgramatically)
    {
        changedProgramatically = false;
        return;
    }
    if(ui->x_to->value() - ui->x_from->value() <= 0)
    {
        ui->warningLabel->setText("Incorrect x range!");
        return;
    }

    plot(false);
}

void MainWindow::on_y_from_valueChanged(double arg1)
{
    if(changedProgramatically)
    {
        changedProgramatically = false;
        return;
    }
    if(ui->y_to->value() - ui->y_from->value() <= 0)
    {
        ui->warningLabel->setText("Incorrect y range!");
        return;
    }

    plot(false);
}

void MainWindow::on_y_to_valueChanged(double arg1)
{
    if(changedProgramatically)
    {
        changedProgramatically = false;
        return;
    }
    if(ui->y_to->value() - ui->y_from->value() <= 0)
    {
        ui->warningLabel->setText("Incorrect y range!");
        return;
    }

    plot(false);
}

void MainWindow::on_pointsNumber_valueChanged(int arg1)
{
    if(!pointsEmpty(functionPoints))
        plot(true);
}

