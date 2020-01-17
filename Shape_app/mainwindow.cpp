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

    type = 0;
    functionEdits.push_back(ui->functionEdit1);
    disableButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

tuple<double, double, double, double> findBoundaries(vector<QPointF> points) //za vector tocaka pronalazi najvece i najmanje x i y vrijednosti
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

void MainWindow::on_selectFile_clicked() //slot za Select file
{
    ui->warningLabel->setText("");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/paula/Diplomski", tr("Text Files (*.txt)")); //"/home/paula/Diplomski"
    if(fileName.isEmpty()){
        return;
    }

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);   

    vector<QPointF> filePoints;
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
           filePoints.push_back(QPointF(x,y));
       }
    }
    file.close();

    if(filePoints.size() < 3)
    {
        ui->warningLabel->setText("File does not contain at least three correctly specified points.");
        return;
    }

    if(sameX(filePoints)) //provjera sadrzi li file tocke s istom x vrijednosti
    {
        ui->warningLabel->setText("File contains points with same x value.");
        return;
    }

    type = 1;
    scene->clear();
    for(int i = 0; i < 5; ++i)
        points[i].clear();
    lines.clear();

    points[0] = filePoints;

    coordinateSystem* system = new coordinateSystem(scene);
    tuple<double, double, double, double> boundaries = findBoundaries(points[0]);
    auto[system_Info_, grid_] =  system->init(scene, get<0>(boundaries), get<1>(boundaries), get<2>(boundaries), get<3>(boundaries)); //elegantniji nacin?
    system_Info = system_Info_;
    grid = grid_;

    for (auto i = points[0].begin(); i != points[0].end(); ++i)
    {
        Point* point = new Point(i->x(), i->y(), transformX(i->x()), transformY(i->y()), scene);
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
       grid->hide();
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

void MainWindow::on_drawButton_clicked() //slot za klik gumba Draw
{
    ui->warningLabel->setText("");
    double xStart = double(ui->doubleSpinBox->value());
    double xEnd = double(ui->doubleSpinBox_2->value());
    double yStart, yEnd;

    if(xEnd - xStart <= 0)
    {
        ui->warningLabel->setText("Incorrect range!");
        return;
    }

    FunctionParser fparser;
    fparser.AddConstant("pi", 3.14159265358979323846);
    fparser.AddConstant("e", 2.71828182845904523536);

    double value[1]; //fja Eval() kod FunctionParsera prima pointer na niz (buduci da iscrtavamo samo fje jedne varijable, taj niz uvijek ima jedan element)

    for(auto i = functionEdits.begin(); i != functionEdits.end(); ++i) //provjera je li neka od funkcija krivo zadana
    {
        if (fparser.Parse((*i)->text().toStdString(), "x") != -1)
        {
            if((*i)->text() != "")
            {
                ui->warningLabel->setText("Incorrectly specified function: f(x) = " + (*i)->text());
                return;
            }
        }
    }

    type = 2;
    scene->clear();
    for(int i = 0; i < 5; ++i)
        points[i].clear();
    lines.clear();

    value[0] = xStart;
    yStart = yEnd = 0;

    int n = -1;
    bool firstPoint = false; //yStart i yEnd postavljamo na prvu definiranu tocku, da ostaje 0 bio bi problem kod npr. -log(x)+10
    for(auto i = functionEdits.begin(); i != functionEdits.end(); ++i) //dodajemo tocke (potrebne za iscrtavanje linija) u vectore i pronalazimo najvecu i najmanju y vrijednost
    {
        n++;
        QString function = (*i)->text();
        if(function == "")
            continue;
        fparser.Parse(function.toStdString(), "x");
        vector<double> x = linspace(xStart, xEnd, 100);
        for(auto j = x.begin(); j != x.end(); ++j)
        {
            value[0] = *j;
            double f_x = fparser.Eval(value);
            if (!fparser.EvalError())
            {
                if(!firstPoint)
                {
                    yStart = yEnd = f_x;
                    firstPoint = true;
                }
                points[n].push_back(QPointF(*j, f_x));
                if(f_x < yStart)
                    yStart = f_x;
                if(f_x > yEnd)
                    yEnd = f_x;
            }
            else
            {
                points[n].push_back(QPointF(numeric_limits<double>::epsilon(),numeric_limits<double>::epsilon()));
                ui->warningLabel->setText("Function f(x) = " + (*i)->text() + " is not defined for the whole range.");
            }
        }
    }

    if(compareDoubles(yStart, yEnd)) //konstantna funkcija
    {
        yStart -= 3;
        yEnd += 3;
    }

    yEnd += 0.02*(yEnd-yStart); //kod postavljanja koordinatnog sustava saljemo malo manje/vece vrijednosti kako bi se izbjeglo iscrtavanje uz sam rub sustava
    yStart -= 0.02*(yEnd-yStart);
    xEnd += 0.02*(xEnd-xStart);
    xStart -= 0.02*(xEnd-xStart);

    coordinateSystem* system = new coordinateSystem(scene);
    auto[system_Info_, grid_] = system->init(scene, xStart, xEnd, yStart, yEnd); //(elegantniji nacin?)
    system_Info = system_Info_;
    grid = grid_;

    createLines(points);
    if(!ui->gridBox->isChecked())
       grid->hide();
}


void MainWindow::on_style_comboBox_currentIndexChanged(int index) //slot za promjenu stila kod iscrtavanja iz datoteke
{
    if(type == 1)
    {
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
    }
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

QString selectColor(int colorNumber)
{
    if(colorNumber == 0)
        return QString("#f5d25d");
    else if(colorNumber == 1)
        return QString("#e69460");
    else if(colorNumber == 2)
        return QString("#e38db6");
    else if(colorNumber == 3)
        return QString("#799bdb");
    else
        return QString("#69d1a7");
}

bool isUndefined(QPointF point)
{
    if(compareDoubles(point.x(), numeric_limits<double>::epsilon()) && compareDoubles(point.y(), numeric_limits<double>::epsilon()))
        return true;
    return false;
}

void MainWindow::createLines(std::vector<QPointF> points[5]) //iscrtavanje linija medu tockama
{                                                            //fja prima argument points (unatoc varijabli clanici points) zbog slucaja iscrtavanja linija za kubicni spline
    QString color;
    for (int n = 0; n < 5; ++n)
    {
        color = selectColor(n);
        if(points[n].empty())
            continue;
        for (auto i = points[n].begin(); i != (points[n].end() - 1); ++i)
        {
            if(isUndefined(*i) || isUndefined(*(i+1)))
                continue;
            connectingLine* line = new connectingLine(transformX(i->x()), transformY(i->y()), transformX((i+1)->x()), transformY((i+1)->y()), color);
            scene->addItem(line);        
            lines.push_back(line);
        }

    }
}

void MainWindow::deleteLines() //brisanje linija
{
    for(int i = 0; i < lines.size(); ++i)
    {
        scene->removeItem(lines.at(i));
        //delete lines.at(i);
    }
    lines.clear();
}

void MainWindow::cubicSpline(std::vector<QPointF> splinePoints[5]) //vector tocaka za iscrtavanje kubicnog spline-a
                                                                   //fja pretpostavlja da je splinePoints prazan
{
    vector<double> X, Y;
    for(auto i = points[0].begin(); i != points[0].end(); ++i)
    {
        X.push_back(i->x());
        Y.push_back(i->y());
    }
    tk::spline s;
    s.set_points(X,Y);
    vector<double> x = linspace(*X.begin(), *(X.end()-1), 1000);
    for(auto i = x.begin(); i != x.end(); ++i)
    {
        splinePoints[0].push_back(QPointF(*i,s(*i)));
    }
}

void MainWindow::on_gridBox_stateChanged(int checked)
{
    if(type != 0)
    {
    if(checked)
        grid->show();
    else
        grid->hide();
    }
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
    for(int i = int(functionEdits.size())-1; i > 0; --i)
        ui->formLayout->removeRow(i);

    functionEdits.clear();
    functionEdits.push_back(ui->functionEdit1);

    ui->functionEdit1->setText("");
    ui->doubleSpinBox->setValue(-1);
    ui->doubleSpinBox_2->setValue(1);

    ui->add_function->setEnabled(true);
    ui->delete_function->setEnabled(false);
    disableButtons();
}

void MainWindow::on_functionEdit1_textEdited()
{
    ui->drawButton->setEnabled(true);
    ui->resetButton->setEnabled(true);
}

void MainWindow::on_doubleSpinBox_valueChanged(double d)
{
    ui->resetButton->setEnabled(true);
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double d)
{
    ui->resetButton->setEnabled(true);
}

//sad:
    //na reset se sve obriše i ostane koordinatni sustav, sve vrati na default
    //includeovi
    //staviti da iscrtava sve osim krivo zadanih, možda povećati labelu za ispis greški
    //poboljšati primjere za točke.. umaskirati za spline
    //labela upozorenja
    //funkcionalnosti..


//za kasnije:
    //template za create lines
    //zacrvenjeno
    //fokus
    //brisanje fja i enable plot gumba
    //vidjeti path za brisanje linija
    //promjena imena
