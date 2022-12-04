#include "mainwindow.h"

#include <QApplication>

// Task HTML Parese
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
