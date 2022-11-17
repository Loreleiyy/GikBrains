#include "mainwindow.h"


#include <QApplication>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QTranslator *t = new QTranslator;
//    t->load("QtLanguage_ru.qm");
//    a.installTranslator(t);
    MainWindow w;


    w.show();
    return a.exec();
}
