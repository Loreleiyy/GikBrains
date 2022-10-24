#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtMath>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ButtonQuEducation1_clicked()
{
    int ax = ui->lineEdit_1_a->text().toInt();
    double bx = ui->lineEdit_1_b->text().toInt();
    int c = ui->lineEdit_1_c->text().toInt();
    QString result;
    if (ax == 0) {
        result = "x=" + QString::number(-c/bx);
        ui->label_qu_education->setText(result);
        return;
    }
    int D = bx*bx - 4*ax*c;
    if (D < 0) {
        result = "нет корней";
        ui->label_qu_education->setText(result);
        return;
    }
    double sqrtD = qSqrt(D);
    qDebug() << ax << ' ' << bx << ' ' << c << ' ' << D <<  ' ' << sqrtD << '\n';
    double x1, x2;
    x1 = resultX(ax, bx, sqrtD);
    result = "x = " + QString::number(x1);
    if (D != 0 ){
        x2 = resultX(ax, bx, -sqrtD);
        result += ", x2 = " + QString::number(x2);
    }
    ui->label_qu_education->setText(result);
}


void MainWindow::on_Button2Triangle_clicked()
{
    double sideA = ui->lineEdit_triangleA->text().toDouble();
    double sideB = ui->lineEdit_triangleB->text().toDouble();
    float angle = ui->lineEdit_triangle_angle->text().toFloat();
    if (ui->radioDegrees->isChecked()) {
        angle = qDegreesToRadians(angle);
    }

    float cosResult = qCos(angle);
    double sqrResult = ((sideA*sideA + sideB*sideB) - (2 * sideA*sideB * cosResult));


    QString result = QString::number(qSqrt(sqrResult));
    ui->label_triangle->setText(result);
}


void MainWindow::on_Button3Add_clicked()
{
    QString str = ui->plainTextEditCopy->toPlainText();
    ui->plainTextEditPaste->appendPlainText(str);
}


void MainWindow::on_Button3Replace_clicked()
{
    QString str = ui->plainTextEditCopy->toPlainText();
    ui->plainTextEditCopy->clear();

    ui->plainTextEditPaste->setPlainText(str);
}


void MainWindow::on_Button3HTML_clicked()
{
    QString str = ui->plainTextEditCopy->toPlainText();
    ui->plainTextEditPaste->setPlainText(str.toHtmlEscaped());

}

double MainWindow::resultX(int a, double b, double sqrD)
{
    double x = (-b+sqrD)/2*a;
    return x;
}

