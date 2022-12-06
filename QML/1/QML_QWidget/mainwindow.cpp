#include "mainwindow.h"

#include <QPushButton>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new QWidget(this);
    widget->parentWidget()->setStyleSheet("background-color: #e5ecef");
    widget->setGeometry(widget->parentWidget()->width() / 3, widget->parentWidget()->height()/3, 300, 250);
    widget->setStyleSheet("background-color: #ffffff;"
                          "border-radius: 5px;");
    QString color = "#535353";
    layout = new QVBoxLayout();
    button = new QPushButton("Вход" ,this);
    //button->setGeometry(10,10,200, 40);
    //button->setMinimumHeight(40);
    button->setMinimumSize(200, 40);
    //button->setSizePolicy(QSizePolicy)
    connect(button, &QPushButton::pressed, this, &MainWindow::buttonPress);
    connect(button, &QPushButton::released, this, &MainWindow::buttonRelease);
    connect(button, &QPushButton::clicked, this, &MainWindow::check);

    lineLogin = new QLineEdit(this);
    lineLogin->setPlaceholderText("Логин");
    setStyleSheet("QLineEdit{ border: 1px solid #000000;"
                  "color: #535353;}");
    buttonStyle();

    linePasword = new QLineEdit(this);
    linePasword->setPlaceholderText("Пароль");
    linePasword->setEchoMode(QLineEdit::Password);
    connect(linePasword, &QLineEdit::returnPressed, this, &MainWindow::check);

    layout->addWidget(lineLogin);
    layout->addWidget(linePasword);
    layout->addWidget(button);
    widget->setLayout(layout);

}

MainWindow::~MainWindow()
{
}

void MainWindow::buttonStyle()
{
    button->setStyleSheet("QPushButton{background-color: #f6f6f6;}"
                          "QPushButton:hover{background-color: #d6d6d6;}");
}

void MainWindow::errorAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(widget, "geometry", this);
    anim->setDuration(25);
    anim->setStartValue(QRect(widget->x()  , widget->y(), 300, 250));
    anim->setEndValue(QRect(widget->x()-5 , widget->y(), 300, 250));

    QPropertyAnimation *anim2 = new QPropertyAnimation(widget, "geometry", this);
    anim2->setDuration(50);
    anim2->setStartValue(QRect(widget->x()  , widget->y(), 300, 250));
    anim2->setEndValue(QRect(widget->x()+10 , widget->y(), 300, 250));

    QPropertyAnimation *anim3 = new QPropertyAnimation(widget, "geometry", this);
    anim3->setDuration(25);
    anim3->setStartValue(QRect(widget->x()  , widget->y(), 300, 250));
    anim3->setEndValue(QRect(widget->x()-5 , widget->y(), 300, 250));


    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);
    group->addAnimation(anim);
    group->addAnimation(anim2);
    group->addAnimation(anim3);
    group->start();
}

void MainWindow::sucessAnim()
{
    QGraphicsOpacityEffect *log = new QGraphicsOpacityEffect(this);
    lineLogin->setGraphicsEffect(log);
    QGraphicsOpacityEffect *pas = new QGraphicsOpacityEffect(this);
    linePasword->setGraphicsEffect(pas);
    QGraphicsOpacityEffect *but = new QGraphicsOpacityEffect(this);
    button->setGraphicsEffect(but);
    QPropertyAnimation *anim = new QPropertyAnimation(log, "opacity", this);
    anim->setDuration(400);
    anim->setEndValue(0);
    QPropertyAnimation *anim2 = new QPropertyAnimation(pas, "opacity", this);
    anim2->setDuration(400);
    anim2->setEndValue(0);
    QPropertyAnimation *anim3 = new QPropertyAnimation(but, "opacity", this);
    anim3->setDuration(400);
    anim3->setEndValue(0);

    QGraphicsOpacityEffect *wid = new QGraphicsOpacityEffect(this);
    widget->setGraphicsEffect(wid);
    QPropertyAnimation *anim4 = new QPropertyAnimation(wid, "opacity", this);
    anim4->setDuration(400);
    anim4->setEndValue(0);
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    group->addAnimation(anim);
    group->addAnimation(anim2);
    group->addAnimation(anim3);

    QSequentialAnimationGroup *groupSe = new QSequentialAnimationGroup(this);
    groupSe->addAnimation(group);
    groupSe->addAnimation(anim4);
    groupSe->start();

}

void MainWindow::buttonPress()
{
    button->setStyleSheet("QPushButton{background-color: #bbbbbb;}");
}

void MainWindow::buttonRelease()
{
    buttonStyle();
}

void MainWindow::check()
{
    if(lineLogin->text() == login && linePasword->text() == pasword){
        sucessAnim();
    }
    else{
        errorAnim();
    }
}

