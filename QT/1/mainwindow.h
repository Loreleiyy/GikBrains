#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButtonQuEducation1_clicked();

    void on_Button2Triangle_clicked();

    void on_Button3Add_clicked();

    void on_Button3Replace_clicked();

    void on_Button3HTML_clicked();

private:
    Ui::MainWindow *ui;
    double resultX(int a, double b, double sqrD);
};
#endif // MAINWINDOW_H
