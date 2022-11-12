#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QApplication>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    translator = new QTranslator(this);
    buttonSetText();

    connect(ui->ButtonNoWrite, &QPushButton::clicked, this, &Widget::openForReading);
    connect(ui->ButtonTranslate, &QPushButton::clicked, this, &Widget::changeLang);
    connect(ui->ButtonDarkTheme, &QPushButton::clicked, this, &Widget::setDarkTheme);
    connect(ui->ButtonLightTheme, &QPushButton::clicked, this, &Widget::setLightTheme);
    fileWidget = new FileSystemWidget(this);
    fileWidget->setGeometry(800, 30, 400, 300);
}

Widget::~Widget()
{
    delete ui;
}

    // Task 5.1  CSS style

void Widget::setDarkTheme()
{
    setStyleSheet("QWidget {"
                "background-color: #222222;"
                  "color: #ccffff;}"
                "QPushButton {"
                  "background-color: #666666;}"
                  );
    ui->plainTextEdit->setStyleSheet("background-color: #333333;"
                                     "color: white}");
}

void Widget::setLightTheme()
{
    setStyleSheet("QWidget {"
                  "background-color: #eeeeee;"
                    "color: black;}"
                  "QPushButton {"
                    "background-color: #cccccc;}");
    ui->plainTextEdit->setStyleSheet("background-color: white;}");
}

    // Task 4.3

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(!Qt::ControlModifier){
        return;
    }
    if(event->key() == Qt::Key::Key_S){
        on_ButtonSave_clicked();
    }
    else if (event->key() == Qt::Key::Key_O){
        on_ButtonOpen_clicked();
    }
    else if (event->key() == Qt::Key::Key_N){
        ui->plainTextEdit->clear();
    }
    else if (event->key() == Qt::Key::Key_Q){
        qApp->quit();
    }
}

void Widget::on_ButtonSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), QDir::current().path(),
                                                    tr("txt(*.txt);; all(*.*)"),
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

void Widget::on_ButtonOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QDir::current().path(), tr("txt(*.txt);; all(*.*)"));
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)){
        QByteArray byte = file.readAll();
        QString fileStr(byte);
        ui->plainTextEdit->setPlainText(fileStr);
        ui->plainTextEdit->setReadOnly(false);
    }
}

void Widget::on_ButtonReference_clicked()
{
    QFile file(":/reference/READme.txt");
    if (file.open(QFile::ReadOnly)){
        QByteArray byte = file.readAll();
        QString fileStr(byte);
        ui->plainTextEdit->setPlainText(fileStr);
    }
}

void Widget::openForReading()
{
    on_ButtonOpen_clicked();
    ui->plainTextEdit->setReadOnly(true);
}

void Widget::changeLang()
{
    if("ru_RU" == translator->language()){
        translator->load("../EditText/EditText/QtLanguage_en.qm");
    }
    else {
        translator->load("../EditText/EditText/QtLanguage_ru.qm");
    }
    qDebug() << translator->language();
    qDebug() << qApp->installTranslator(translator);
    buttonSetText();
}



void Widget::buttonSetText()
{
    ui->ButtonNoWrite->setText(tr("Read-only"));
    ui->ButtonTranslate->setText(tr("Language"));
    ui->ButtonOpen->setText(tr("Open"));
    ui->ButtonReference->setText(tr("Reference"));
    ui->ButtonSave->setText(tr("Save"));
    ui->ButtonDarkTheme->setText(tr("Dark Theme"));
    ui->ButtonLightTheme->setText(tr("Light Theme"));
}

