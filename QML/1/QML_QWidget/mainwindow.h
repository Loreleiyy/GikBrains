#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QPushButton *button;
    QLineEdit *lineLogin;
    QLineEdit *linePasword;
    QWidget *widget;
    QVBoxLayout *layout;
    QString login = "login";
    QString pasword = "pasword";

    void buttonStyle();
    void errorAnim();
    void sucessAnim();


private slots:
    void buttonPress();
    void buttonRelease();
    void check();
};
#endif // MAINWINDOW_H
