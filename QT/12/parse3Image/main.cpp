#include "mainwindow.h"

#include <QApplication>
#include <QSslSocket>


// img_href":"h
// "
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString()
    //         << QSslSocket::sslLibraryVersionString();
    MainWindow w;
    w.show();
    return a.exec();
}
