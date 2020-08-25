#include "function.h"
#include "ui_function.h"

Function::Function(QString color_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Function)
{
    ui->setupUi(this);
    color = color_;
    ui->functionLabel->setStyleSheet("color: "+ color);
    ui->functionEdit->setStyleSheet("color: "+ color +";\nbackground-color: #1C1C1C;");
    name = "";
}

Function::~Function()
{
    delete ui;
}


QString Function::generatePoints(double xStart, double xEnd, int numberPoints)
{
    FunctionParser parser;
    parser.AddConstant("pi", 3.14159265358979323846);
    parser.AddConstant("e", 2.71828182845904523536);

    QString returnMessage = "";
    double value[1]; //funkcija Eval() kod FunctionParsera prima pointer na niz (buduci da iscrtavamo samo fje jedne varijable, taj niz uvijek ima jedan element)
    points.clear();
    value[0] = xStart;
    if (parser.Parse(name.toStdString(), "x") != -1)
    {
        if(name != "")
            return "Incorrectly specified function: f(x) = " + name + "\n\n";
        else
            return "";
    }

    QVector<double> x = Utility::linspace(xStart, xEnd, numberPoints);
    for(auto i = x.begin(); i != x.end(); ++i)
    {
        value[0] = *i;
        double f_x = parser.Eval(value);
        if (!parser.EvalError())
            points.push_back(QPointF(*i, f_x));
        else
        {
            points.push_back(QPointF(std::numeric_limits<double>::epsilon(),std::numeric_limits<double>::epsilon()));
            returnMessage = "Function f(x) = " + name + " is not defined for the whole range.\n\n";
        }
    }
    return returnMessage;
}


void Function::on_functionEdit_textEdited(const QString &arg1)
{
    ui->functionEdit->setStyleSheet("color: "+ color+";\nbackground-color: #1C1C1C;");
}

void Function::on_functionEdit_editingFinished()
{
    FunctionParser parser;
    parser.AddConstant("pi", 3.14159265358979323846);
    parser.AddConstant("e", 2.71828182845904523536);

    name = ui->functionEdit->text();
    if(parser.Parse(name.toStdString(), "x") != -1)
       if(name != "")
            ui->functionEdit->setStyleSheet("border: 2px solid #850000;\ncolor: "+ color+";\nbackground-color: #1C1C1C;");
    emit plotSignal(true);
}

void Function::on_deleteFunction_clicked()
{
    emit deleteFunctionSignal(this);
}
