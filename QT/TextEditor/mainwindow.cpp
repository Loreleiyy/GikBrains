#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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


void MainWindow::on_ButtonSave_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить", QDir::current().path(),
                                                    "Текст(*.txt);; Все(*.*)",
                                                    nullptr,QFileDialog::DontConfirmOverwrite);
    if(fileName.isEmpty()) return;
    if (fileName.indexOf('.') == -1){           // if no extension is specified
        fileName += ".txt";
    }
    QFile file(fileName);
    if (file.open(QFile::WriteOnly)){
        QString saveToFile = ui->plainTextEdit->toPlainText();
        QByteArray byte = saveToFile.toUtf8();
        file.write(byte);
    }
}


void MainWindow::on_ButtonOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть", QDir::current().path(), "Текст(*.txt);; Все(*.*)");
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)){
        QByteArray byte = file.readAll();
        QString fileStr(byte);
        ui->plainTextEdit->setPlainText(fileStr);
    }
}


void MainWindow::on_ButtonReference_clicked()
{
    QFile file(":/reference/READme.txt");
    if (file.open(QFile::ReadOnly)){
        QByteArray byte = file.readAll();
        QString fileStr(byte);
        ui->plainTextEdit->setPlainText(fileStr);
    }
}

