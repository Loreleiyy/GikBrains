#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QApplication>
#include <QDebug>
#include <QPoint>
#include <QToolBar>
#include <QPrinter>
#include <QPrintDialog>
#include <QStyle>
#include <QGridLayout>
#include <QFontDialog>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    translator = new QTranslator;

    setCentralWidget(ui->textEdit);

        // Task 6.3 multi-document interface

//    mid = new QMdiArea(this);
//    QGridLayout *lay = new QGridLayout(this);
//    ui->centralwidget->setLayout(lay);
//    lay->addWidget(mid, 0, 0, 10,10);
//    mid->addSubWindow(ui->textEdit);
//    mid->addSubWindow(new QtextEdit(this));


       // Task 6.1 add menu
    menu = menuBar()->addMenu("File");
    action["Save"] = menu->addAction("Save");
    connect(action.value("Save"), &QAction::triggered, this, &MainWindow::onSave);

    action["Open"] = menu->addAction("Open");
    connect(action.value("Open"), &QAction::triggered, this, &MainWindow::onOpen);

    action["Read-Only"] = menu->addAction("Read-Only");
    connect(action.value("Read-Only"), &QAction::triggered, this, &MainWindow::openForReading);

    action["Reference"] = menu->addAction("Reference");
    connect(action.value("Reference"), &QAction::triggered, this, &MainWindow::onReference);

    actLanguage = menu->addMenu("Language");
    action["English"] = actLanguage->addAction("English");

    connect(action.value("English"), &QAction::triggered, this, &MainWindow::setEnglish);

    action["Русский"] = actLanguage->addAction("Русский");

    connect(action.value("Русский"), &QAction::triggered, this, &MainWindow::setRu);

    actTheme = menu->addMenu("Change Theme");
    action["Dark"] = actTheme->addAction("Dark");

    connect(action.value("Dark"), &QAction::triggered, this, &MainWindow::setDarkTheme);

    action["Light"] = actTheme->addAction("Light");

    connect(action.value("Light"), &QAction::triggered, this, &MainWindow::setLightTheme);
    format = menuBar()->addMenu("Format");

    // Task 7.1 Format
    action["Copy Format"] = format->addAction("Copy Format");
    connect(action.value("Copy Format"), &QAction::triggered, this, &MainWindow::copyFormat);
    action["Paste Format"] = format->addAction("Paste Format");
    connect(action.value("Paste Format"), &QAction::triggered, this, &MainWindow::pasteFormat);
    action["Font"] = format->addAction("Font");
    connect(action.value("Font"), &QAction::triggered, this, &MainWindow::newFont);

    action["on Left Edge"] = format->addAction("on Left Edge");
    connect(action.value("on Left Edge"), &QAction::triggered, this, &MainWindow::onLeftEdge);
    action["on Right Edge"] = format->addAction("on Right Edge");
    connect(action.value("on Right Edge"), &QAction::triggered, this, &MainWindow::onRightEdge);
    action["on Center"] = format->addAction("on Center");
    connect(action.value("on Center"), &QAction::triggered, this, &MainWindow::onCenter);


        // Task 6.2 print
    QToolBar *tbar = addToolBar("ToolBar");
    action["Print"] = tbar->addAction("Print");
    tbar->setMovable(false);
    connect(action.value("Print"), &QAction::triggered, this, &MainWindow::print);

    buttonSetText();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onSave()
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
        QString saveToFile = ui->textEdit->toPlainText();
        QByteArray byte = saveToFile.toUtf8();
        file.write(byte);
    }
}


void MainWindow::onOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QDir::current().path(), tr("txt(*.txt);; all(*.*)"));
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)){
        QByteArray byte = file.readAll();
        QString fileStr(byte);
        ui->textEdit->setPlainText(fileStr);
        ui->textEdit->setReadOnly(false);
    }
}


void MainWindow::onReference()
{
    QFile file(":/reference/READme.txt");
    if (file.open(QFile::ReadOnly)){
        QByteArray byte = file.readAll();
        QString fileStr(byte);
        ui->textEdit->setPlainText(fileStr);
    }
}

void MainWindow::openForReading()
{
    onOpen();
    ui->textEdit->setReadOnly(true);
}

    // Task 5.1  CSS style

void MainWindow::setDarkTheme()
{

    setStyleSheet("QWidget {"
                "background-color: #222222;"
                  "color: #ccffff;}"
                "QPushButton {"
                  "background-color: #666666;}"
                  );
    ui->textEdit->setStyleSheet("background-color: #333333;"
                                     "color: white}");
}

void MainWindow::setLightTheme()
{
    setStyleSheet("QWidget {"
                  "background-color: #eeeeee;"
                    "color: black;}"
                  "QPushButton {"
                    "background-color: #cccccc;}");
    ui->textEdit->setStyleSheet("background-color: white;}");
}

void MainWindow::setEnglish()
{
    translator->load("../TextEditor/QtLanguage_en.qm");
    qDebug() << translator->language();
    qDebug() << qApp->installTranslator(translator);
    buttonSetText();
}

void MainWindow::setRu()
{
    translator->load("../TextEditor/QtLanguage_ru.qm");
    qDebug() << translator->language();
    qDebug() << qApp->installTranslator(translator);
    buttonSetText();
}

void MainWindow::print()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print"));
    if (dialog.exec() == QDialog::Accepted){
        ui->textEdit->print(&printer);
    }
}

void MainWindow::copyFormat()
{
    QTextBlockFormat f = ui->textEdit->textCursor().blockFormat();
    form = &f;
}

void MainWindow::pasteFormat()
{
    ui->textEdit->textCursor().setBlockFormat(*form);
}

void MainWindow::newFont()
{
    QFont font = ui->textEdit->textCursor().charFormat().font();
    QFontDialog dialog(font, this);
    bool b = true;
    font = dialog.getFont(&b);
    if (b){
        QTextCharFormat chForm;
        chForm.setFont(font);
        ui->textEdit->textCursor().setCharFormat(chForm);
    }
}

void MainWindow::onLeftEdge()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::onRightEdge()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::onCenter()
{
    ui->textEdit->setAlignment(Qt::AlignHCenter);
}

void MainWindow::buttonSetText()
{

    menu->setTitle(tr("File"));
    actLanguage->setTitle(tr("Language"));
    actTheme->setTitle(tr("Change Theme"));
    format->setTitle(tr("Format"));
    action.value("Save")->setText(tr("Save"));
    action.value("Open")->setText(tr("Open"));
    action.value("Read-Only")->setText(tr("Read-Only"));
    action.value("Reference")->setText(tr("Reference"));
    action.value("Dark")->setText(tr("Dark"));
    action.value("Light")->setText(tr("Light"));
    action.value("Print")->setText(tr("Print"));
    action.value("Copy Format")->setText(tr("Copy Format"));
    action.value("Paste Format")->setText(tr("Paste Format"));
    action.value("Font")->setText(tr("Font"));
    action.value("on Left Edge")->setText(tr("on Left Edge"));
    action.value("on Right Edge")->setText(tr("on Right Edge"));
    action.value("on Center")->setText(tr("on Center"));
}
