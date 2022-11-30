#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>

#include "downloader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Downloader *downloader;
    QProgressBar *progress;
    QLineEdit *text;
    QPushButton *button;

private slots:
    void showPic(const QString&);
    void slotGo();

    void downloadProgress(qint64, qint64);
};
#endif // MAINWINDOW_H
