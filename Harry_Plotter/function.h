#ifndef FUNCTION_H
#define FUNCTION_H

#include <QWidget>
#include "fparser.hh"
#include "utility.h"

namespace Ui {
class Function;
}

class Function : public QWidget
{
    Q_OBJECT

public:
    explicit Function(QString color_, QWidget *parent = nullptr);
    ~Function();
    QString name;
    QString color;
    QVector<QPointF> points;

    QString generatePoints(double xStart, double xEnd, int numberPoints);

signals:
    void deleteFunctionSignal(Function *function);
    void plotSignal(bool automatic);

private slots:

    void on_functionEdit_textEdited(const QString &arg1);

    void on_functionEdit_editingFinished();

    void on_deleteFunction_clicked();

private:
    Ui::Function *ui;

};

#endif // FUNCTION_H
