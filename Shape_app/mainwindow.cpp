#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectingline.h"
#include "coordinatesystem.h"
#include "point.h"
#include "fparser.hh"
#include "spline.h"

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
    disableButtons();
    grid = new QGraphicsItemGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::transformX(double x) //transformira x vrijednost u onu koja ce se iscrtati na ekranu (u ovisnosti o koordinatnom sustavu)
{
    double xStart = get<0>(system_Info);
    double xStep = get<2>(system_Info);
    return x1 + (x-xStart)*xStep;
}

double MainWindow::transformY(double y) //transformira y vrijednost u onu koja ce se iscrtati na ekranu (u ovisnosti o koordinatnom sustavu)
{
    double yStart = get<1>(system_Info);
    double yStep = get<3>(system_Info);
    return scene->height()-y2 - (y-yStart)*yStep;
}

bool compareDoubles(double a, double b) //provjera jednakosti dva double broja
{
   double diff = a - b;
   return (diff < numeric_limits<double>::epsilon()) && (diff > -numeric_limits<double>::epsilon());
}

bool sameX(vector<QPointF> points) //vraca true ako vector sadrzi tocke s istom x vrijednosti
{
    sort(points.begin(), points.end());
    for(auto i = points.begin(); i != points.end() - 1; ++i)
    {
        if(compareDoubles(i->x(), (i+1)->x()))
            return true;
    }
    return false;
}

QString selectColor(int colorNumber)
{
    switch(colorNumber)
    {
        case(0):
            return QString("#f5d25d");
        case(1):
            return QString("#e69460");
        case(2):
            return QString("#e67cae");
        case(3):
            return QString("#799bdb");
        case(4):
            return QString("#69d1a7");
        case(5):
            return QString("#edbc18");
        case(6):
            return QString("#e36c20");
        case(7):
            return QString("#e84391");
        case(8):
            return QString("#4277db");
        default:
            return QString("#17bd79");
    }
}

int MainWindow::firstEmpty(bool type)   //vraca int slobodnog mjesta za function edit/file label
                                        //type - 0 za file, 1 za funkcije
{
    if(type)
    {
        if(functionEdits.size() < 5)
            return int(functionEdits.size());
        int n = 0;
        for(auto i = functionEdits.begin(); i != functionEdits.end(); ++i)
        {
            if(!(*i))
                return n;
            ++n;
        }
        return -1;
    }
    else
    {
        if(fileLabels.size() < 5)
            return int(fileLabels.size());
        int n = 0;
        for(auto i = fileLabels.begin(); i != fileLabels.end(); ++i)
        {
            if(!(*i))
                return n;
            ++n;
        }
        return -1;
    }
}

int MainWindow::numberElements(bool type)
{
    int n = 0;
    if(type)
    {
        for(auto i = functionEdits.begin(); i != functionEdits.end(); ++i)
            if(*i)
                ++n;
        return n;
    }
    else
    {
        for(auto i = fileLabels.begin(); i != fileLabels.end(); ++i)
            if(*i)
                ++n;
        return n;
    }
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

vector<QPointF> cubicSpline(vector<QPointF> points) //vector tocaka za iscrtavanje kubicnog spline-a

{
    vector<QPointF> splinePoints(1000);
    vector<double> X, Y;
    for(auto i = points.begin(); i != points.end(); ++i)
    {
        X.push_back(i->x());
        Y.push_back(i->y());
    }
    tk::spline s;
    s.set_points(X,Y);
    vector<double> x = linspace(*X.begin(), *(X.end()-1), 1000);
    int n = 0;
    for(auto i = x.begin(); i != x.end(); ++i)
    {
        splinePoints[n] = QPointF(*i,s(*i));
        ++n;
    }
    return splinePoints;
}

void MainWindow::on_selectFile_clicked() //slot za Select file
{
    ui->warningLabel->setText("");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/paula/Diplomski", tr("Text Files (*.txt)")); //"/home/paula/Diplomski"
    if(fileName.isEmpty()){
        return;
    }

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    int position = firstEmpty(0);
    int fileNumber = numberElements(0);

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

    if(fileNumber == 5)
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

    //ui->delete_function->setEnabled(true);
    ui->resetButton->setEnabled(true);

    if(points.size() < 3)
    {
        ui->warningLabel->setText("File does not contain at least three correctly specified points.");
        return;
    }

    if(sameX(points)) //provjera sadrzi li file tocke s istom x vrijednosti
    {
        ui->warningLabel->setText("File contains points with same x value.");
        return;
    }

    sort(points.begin(), points.end());
    filePoints[position] = points;
    splinePoints[position] = cubicSpline(points);

   /* coordinateSystem* system = new coordinateSystem(scene);
    tuple<double, double, double, double> boundaries = findBoundaries(points[0]);
    auto[system_Info_, grid_] =  system->init(scene, get<0>(boundaries), get<1>(boundaries), get<2>(boundaries), get<3>(boundaries)); //elegantniji nacin?
    system_Info = system_Info_;
    grid = grid_;

    for (auto i = points[0].begin(); i != points[0].end(); ++i)
    {
        Point* point = new Point(i->x(), i->y(), transformX(i->x()), transformY(i->y()), "white", scene);
        scene->addItem(point);
    }

    sort(points[0].begin(), points[0].end());

    if(ui->style_comboBox->currentIndex() == 1)
       createLines(points);
    else if(ui->style_comboBox->currentIndex() == 2)
    {
        vector<QPointF> splinePoints[5];
        cubicSpline(splinePoints);
        createLines(splinePoints);
    }

    if(!ui->gridBox->isChecked())
       grid->hide();*/
}

bool isUndefined(QPointF point)
{
    if(compareDoubles(point.x(), numeric_limits<double>::epsilon()) && compareDoubles(point.y(), numeric_limits<double>::epsilon()))
        return true;
    return false;
}

void pushPoints(vector<QPointF> points[5], vector<double>* Y, double xStart, double xEnd)
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

void MainWindow::yBoundaries(double* yStart, double* yEnd, double xStart, double xEnd)
{
    vector<double> Y;
    pushPoints(functionPoints, &Y, xStart, xEnd);
    pushPoints(filePoints, &Y, xStart, xEnd);
    if(ui->style_comboBox->currentIndex() == 2)
        pushPoints(splinePoints, &Y, xStart, xEnd);

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
    for(int i = 0; i < Y.size(); ++i)
        qDebug() << Y[i];
}

void MainWindow::plot(QPointF xRange, QPointF yRange)
{
    ui->warningLabel->setText("");
    double xStart, xEnd, yStart, yEnd;

    xStart = double(ui->x_from->value());
    xEnd = double(ui->x_to->value());

    if(xRange.isNull())
    {
        //naci max od tocaka filePoints
        //ako veci staviti ga
    }

    FunctionParser fparser;
    fparser.AddConstant("pi", 3.14159265358979323846);
    fparser.AddConstant("e", 2.71828182845904523536);

    double value[1]; //fja Eval() kod FunctionParsera prima pointer na niz (buduci da iscrtavamo samo fje jedne varijable, taj niz uvijek ima jedan element)

    scene->clear();
    for(int i = 0; i < 5; ++i)
        functionPoints[i].clear();

    value[0] = xStart;

    int n = -1;
    for(auto i = functionEdits.begin(); i != functionEdits.end(); ++i) //dodajemo tocke (potrebne za iscrtavanje linija) u vectore i pronalazimo najvecu i najmanju y vrijednost
    {
        n++;
        if (fparser.Parse((*i)->text().toStdString(), "x") != -1)
        {
            if((*i)->text() != "")
                ui->warningLabel->setText("Incorrectly specified function: f(x) = " + (*i)->text());
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
                ui->warningLabel->setText("Function f(x) = " + (*i)->text() + " is not defined for the whole range.");
            }
        }
    }

    if(yRange.isNull())
    {
        yBoundaries(&yStart, &yEnd, xStart, xEnd);

        ui->y_from->setValue(yStart);
        ui->y_to->setValue(yEnd);
    }
    else
    {
        yStart = ui->y_from->value();
        yEnd = ui->y_to->value();
    }

    ui->x_from->setValue(xStart);
    ui->x_to->setValue(xEnd);

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


void MainWindow::on_drawButton_clicked()
{
    plot(QPointF(), QPointF());
}


void MainWindow::on_style_comboBox_currentIndexChanged(int index) //slot za promjenu stila kod iscrtavanja iz datoteke
{
        /*
        if(index == 0)
           deleteLines();
        else if(index == 1)
        {
            deleteLines();
            createLines(points);
        }
        else
        {
            deleteLines();
            vector<QPointF> splinePoints[5];
            cubicSpline(splinePoints);
            createLines(splinePoints);
        }
    }*/
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

void MainWindow::createPoints()
{
    for(int n = 0; n < 5; ++n)
    {
        if(filePoints[n].empty())
            continue;

        for (auto i = filePoints[n].begin(); i != filePoints[n].end(); ++i)
        {
            Point* point = new Point(i->x(), i->y(), transformX(i->x()), transformY(i->y()), selectColor(n+5), scene);
            scene->addItem(point);
        }
    }
}

void MainWindow::createLines() //iscrtavanje linija medu tockama
{
    QString color;
    for (int n = 0; n < 5; ++n)
    {
        color = selectColor(n);
        if(functionPoints[n].empty())
            continue;
        for (auto i = functionPoints[n].begin(); i != (functionPoints[n].end() - 1); ++i)
        {
            if(isUndefined(*i) || isUndefined(*(i+1)))
                continue;
            connectingLine* line = new connectingLine(transformX(i->x()), transformY(i->y()), transformX((i+1)->x()), transformY((i+1)->y()), color, functionEdits[unsigned(n)]->text(), scene);
            scene->addItem(line);        
        }
    }

    if(ui->style_comboBox->currentIndex() == 1)
    {
        for (int n = 0; n < 5; ++n)
        {
            color = selectColor(n+5);
            if(filePoints[n].empty())
                continue;
            for (auto i = filePoints[n].begin(); i != (filePoints[n].end() - 1); ++i)
            {
                connectingLine* line = new connectingLine(transformX(i->x()), transformY(i->y()), transformX((i+1)->x()), transformY((i+1)->y()), color, "", scene);
                scene->addItem(line);
            }
        }
    }

    else if(ui->style_comboBox->currentIndex() == 2)
    {
        for (int n = 0; n < 5; ++n)
        {
            color = selectColor(n+5);
            if(splinePoints[n].empty())
                continue;
            for (auto i = splinePoints[n].begin(); i != (splinePoints[n].end() - 1); ++i)
            {
                connectingLine* line = new connectingLine(transformX(i->x()), transformY(i->y()), transformX((i+1)->x()), transformY((i+1)->y()), color, "", scene);
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
    ui->resetButton->setEnabled(true);
}

void MainWindow::disableButtons() //onemogucuje gumbe za crtanje i reset
{
    ui->drawButton->setEnabled(false);
    ui->resetButton->setEnabled(false);
}

void MainWindow::on_delete_function_clicked()
{
    functionEdits.pop_back();
    ui->formLayout->removeRow(int(functionEdits.size()));

    if(int(functionEdits.size()) == 1)
        ui->delete_function->setEnabled(false);

    ui->add_function->setEnabled(true);    
}

void MainWindow::on_resetButton_clicked() //defaultne postavke i onemogucavanje odgovarajucih gumba
{
    for(int i = numberElements(1)-1; i > 0; --i)
        ui->formLayout->removeRow(i);

    for(int i = numberElements(0)-1; i >= 0; --i)
        ui->formLayout_2->removeRow(i);

    functionEdits.clear();
    functionEdits.push_back(ui->functionEdit1);
    fileLabels.clear();
    fileBoxes.clear();

    ui->functionEdit1->setText("");
    ui->warningLabel->setText("");
    ui->x_from->setValue(-3);
    ui->x_to->setValue(3);
    ui->y_from->setValue(-3);
    ui->y_to->setValue(3);
    ui->pointsNumber->setValue(101);
    ui->style_comboBox->setCurrentIndex(0);
    ui->gridBox->setCheckState(Qt::CheckState(false));

    clearPoints();

    ui->add_function->setEnabled(true);
    ui->delete_function->setEnabled(false);
    disableButtons();

    plot(QPointF(), QPointF()); //provjeriti za eneablanje gumbi, za checkboxove kod fileova
}

void MainWindow::on_functionEdit1_textEdited()
{
    ui->drawButton->setEnabled(true);
    ui->resetButton->setEnabled(true);
}

void MainWindow::on_x_from_valueChanged(double d)
{
    ui->resetButton->setEnabled(true);

   /* if(xEnd - xStart <= 0)
    {
        ui->warningLabel->setText("Incorrect range!");
        return;
    }*/
}

void MainWindow::on_x_to_valueChanged(double d)
{
    ui->resetButton->setEnabled(true);
}

//sad:
    //crte ne bjeze iz sustava
    //splajn racuna za cijeli range
    //min max xRange

    //includeovi
    //labela za greske
    //urediti ponavljanja koda..
    //poboljšati primjere za točke.. umaskirati za spline
    //funkcionalnosti.. //if startText-->text == "get started" nista else plot()
    //zacrvenjeno
    //promijeniti komentare
    //srediti reset, srediti na što se sve eneabla
    //promijeniti boje funkcija i velicine tocki

//kasnije:
    //template za create lines
    //fokus
    //vidjeti path za brisanje linija


// ime, gitignore, parser, dinamicki slotovi - brisanje fja i enable plot gumba
