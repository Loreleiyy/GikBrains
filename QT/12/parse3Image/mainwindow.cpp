#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QGridLayout>
#include <QMessageBox>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    downloader = new Downloader(this);
    progress = new QProgressBar(this);
    text = new QLineEdit(this);
    button = new QPushButton("Search", this);
    connect(button, &QPushButton::clicked, this, &MainWindow::slotGo);
    connect(downloader, &Downloader::doneFile, this, &MainWindow::showPic);
    connect(downloader, &Downloader::downloadProgress, this, &MainWindow::downloadProgress);

    QGridLayout *layout = new QGridLayout();

    layout->addWidget(text, 0, 0);
    layout->addWidget(button, 0, 1);
    layout->addWidget(progress, 1, 0, 1, 2);

    QWidget *widg = new QWidget(this);
    setCentralWidget(widg);
    widg->setLayout(layout);

}

MainWindow::~MainWindow()
{
}


void MainWindow::showPic(const QString& str)
{
        QPixmap pix(str);

        QLabel *labl = new QLabel();
        labl->setPixmap(pix.scaled(pix.size()/3));

        labl->show();
}

void MainWindow::slotGo()
{

    QString str = text->text();
    downloader->setRequest(str);

}



void MainWindow::downloadProgress(qint64 receiv, qint64 total)
{

    if(total<=0)return;
    progress->setValue(100*receiv / total);
}

