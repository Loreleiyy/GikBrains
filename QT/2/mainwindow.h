#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>


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
    void on_TextSpecChar_textChanged();

    void on_Button2Add_clicked();

    void on_Button2Delete_clicked();

    void on_checkIcon_stateChanged(int arg1);

    void on_Button3Color_clicked();



private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

};
#endif // MAINWINDOW_H
